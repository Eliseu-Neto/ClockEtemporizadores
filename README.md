Fechadura Eletrônica com RFID, Senha e Controle de Lâmpadas Inteligentes

1. Escopo do Projeto
Apresentação do Projeto
O projeto consiste em uma fechadura eletrônica que permite o destravamento por meio de um cartão RFID ou inserção de uma senha numérica. O sistema também inclui um controle de lâmpadas inteligentes por meio de um joystick, permitindo o ajuste da intensidade luminosa, seleção da lâmpada a ser controlada e o acionamento remoto das lâmpadas.
Título do Projeto!
Fechadura Eletrônica Inteligente com RFID, Senha e Controle de Lâmpadas
Objetivos do Projeto
•	Desenvolver um sistema de controle de acesso seguro e eficiente;
•	Integrar um método duplo de autenticação (RFID e teclado matricial);
•	Registrar os acessos na EEPROM para monitoramento posterior;
•	Fornecer feedback sonoro e visual sobre o status da fechadura;
•	Adicionar a funcionalidade de controle de lâmpadas inteligentes por meio de um joystick, incluindo seleção de qual lâmpada será controlada.
Descrição do Funcionamento
1.	O sistema permanece bloqueado até que um usuário apresente um cartão RFID autorizado ou insira uma senha válida no teclado.
2.	Se a autenticação for bem-sucedida, o servo motor libera a fechadura por um tempo predefinido.
3.	O LED e o buzzer fornecem feedback para indicar acesso concedido ou negado.
4.	Os acessos são armazenados na EEPROM para posterior consulta.
5.	O joystick é utilizado para selecionar qual lâmpada será controlada e, em seguida, ajustar a intensidade luminosa ou ligar/desligar a lâmpada escolhida.
Justificativa
A necessidade de um sistema de segurança moderno, de baixo custo e confiável motiva este projeto. Com a adição do controle de lâmpadas e a seleção da lâmpada específica, ele também oferece uma solução prática para iluminação automatizada.
Originalidade
O projeto se diferencia por combinar RFID, senha numérica e controle de lâmpadas inteligentes com a funcionalidade de seleção de lâmpada a ser controlada, oferecendo mais segurança e conveniência para diferentes cenários de uso.

2. Especificação do Hardware
Diagrama em Bloco
•	Entrada: RFID RC522, Teclado Matricial 4x4, Joystick
•	Processamento: RP2040 (BitDogLab)
•	Saída: Servo motor, Buzzer, LED indicador, Lâmpadas inteligentes
•	Armazenamento: EEPROM interna
Função de Cada Bloco!
•	RFID RC522: Lê cartões RFID e verifica a autenticidade do usuário.
•	Teclado Matricial: Permite a inserção de senhas numéricas.
•	Joystick: Seleciona qual lâmpada controlar e ajusta a intensidade e estado da lâmpada escolhida.
•	RP2040: Processa as informações e gerencia a lógica de controle.
•	Servo Motor: Aciona a fechadura mecânica.
•	Buzzer e LED: Indicadores visuais e sonoros.
•	EEPROM: Armazena histórico de acessos.
•	Módulo de comunicação sem fio: Permite interação com lâmpadas inteligentes.
Circuito Completo
O hardware será montado na BitDogLab, utilizando a RP2040 como unidade de controle, ligada aos periféricos conforme especificação.

3. Especificação do Firmware
Definição das Variáveis!
•	rfidTag (String) – ID do cartão RFID lido
•	senhaDigitada (Array) – Armazena senha digitada
•	acessoPermitido (Boolean) – Indica se a entrada foi autorizada
•	joystickX (Int) – Captura movimento horizontal do joystick (seleciona a lâmpada)
•	joystickY (Int) – Captura movimento vertical do joystick (ajusta intensidade luminosa)
•	lampadaSelecionada (Int) – Indica qual lâmpada está sendo controlada
•	lampadaStatus[] (Boolean) – Liga/desliga cada lâmpada
•	intensidadeLuminosa[] (Int) – Define a intensidade de cada lâmpada
Fluxograma!
1.	Inicia sistema
2.	Aguarda entrada (RFID ou Senha)
3.	Verifica credenciais
4.	Se autorizado, libera fechadura e registra acesso
5.	Aguarda entrada do joystick
6.	Seleciona a lâmpada a ser controlada
7.	Ajusta intensidade luminosa ou liga/desliga lâmpada selecionada
8.	Retorna ao modo de espera

https://github.com/Eliseu-Neto/ClockEtemporizadores.git 
https://drive.google.com/drive/u/1/folders/1fg6HFhCMbDNeBVorSOZFuLws8P_LDanM 
