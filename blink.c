#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define RST_PIN         9
#define SS_PIN          10
#define SERVO_PIN       3
#define JOYSTICK_X      A0
#define JOYSTICK_Y      A1
#define BUZZER_PIN      6
#define LED_PIN         7
#define NUM_LAMPADAS    3

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int lampadaSelecionada = 0;
bool lampadaStatus[NUM_LAMPADAS] = {false, false, false};
int intensidadeLuminosa[NUM_LAMPADAS] = {0, 0, 0};
char senhaCorreta[] = "1234";
char senhaDigitada[4];
int senhaIndex = 0;

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    servo.attach(SERVO_PIN);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pwm.begin();
    pwm.setPWMFreq(1600);
}

void loop() {
    verificarRFID();
    verificarSenha();
    controlarLampadas();
}

void verificarRFID() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    String tagID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        tagID += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(tagID);
    if (tagID == "a1b2c3d4") {
        abrirFechadura();
    } else {
        negarAcesso();
    }
}

void verificarSenha() {
    if (Serial.available() > 0) {
        char digito = Serial.read();
        if (isdigit(digito)) {
            senhaDigitada[senhaIndex++] = digito;
            if (senhaIndex == 4) {
                senhaDigitada[senhaIndex] = '\0';
                if (strcmp(senhaDigitada, senhaCorreta) == 0) {
                    abrirFechadura();
                } else {
                    negarAcesso();
                }
                senhaIndex = 0;
            }
        }
    }
}

void abrirFechadura() {
    servo.write(90);
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    servo.write(0);
    digitalWrite(LED_PIN, LOW);
}

void negarAcesso() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(BUZZER_PIN, LOW);
        delay(200);
    }
}

void controlarLampadas() {
    int x = analogRead(JOYSTICK_X);
    int y = analogRead(JOYSTICK_Y);

    if (x < 400) {
        lampadaSelecionada = (lampadaSelecionada - 1 + NUM_LAMPADAS) % NUM_LAMPADAS;
        delay(200);
    } else if (x > 600) {
        lampadaSelecionada = (lampadaSelecionada + 1) % NUM_LAMPADAS;
        delay(200);
    }

    if (y < 400) {
        intensidadeLuminosa[lampadaSelecionada] = max(0, intensidadeLuminosa[lampadaSelecionada] - 20);
    } else if (y > 600) {
        intensidadeLuminosa[lampadaSelecionada] = min(255, intensidadeLuminosa[lampadaSelecionada] + 20);
    }

    pwm.setPWM(lampadaSelecionada, 0, intensidadeLuminosa[lampadaSelecionada] * 16);
}
