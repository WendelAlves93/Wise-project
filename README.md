# README

## Projeto: Controle de Estufa (EM DESENVOLVIMENTO)

Este projeto tem como objetivo controlar o nível de água em uma caixa d'água utilizando dois sensores de boia. Quando o nível de água estiver baixo, a bomba de poço será acionada para encher a caixa d'água. Além disso, também há um sensor de umidade do solo que aciona uma válvula solenoide para fornecer água às plantas quando necessário. O projeto também utiliza um sensor DHT11 para medir a umidade e temperatura do ar.

As informações coletadas pelos sensores são enviadas para outro Arduino usando o protocolo LoRa. O lado receptor tem um receptor LoRa que recebe as informações e as envia para o Arduino, que as envia para a nuvem e apresenta os dados em uma dashboard.

## Lista de tarefas
-[] Desenvolvimento do prototipo (HARDWARE)
-[x] Desenvolvimento do prototipo (SOFTWARE)
-[] Finalizar apresentação 

[Apresentação do PowerPoint] (link)
## Requisitos
- Arduino Uno ou similar
- Módulo LoRa
- Sensores de boia x2
- Sensor de umidade do solo
- Sensor DHT11
- Bomba de poço
- Válvula solenoide
- Cabos e protoboard para montagem

## Instalação
1. Faça o download do código-fonte deste projeto.
2. Conecte os sensores e atuadores ao Arduino conforme o esquema de montagem.
3. Carregue o código-fonte para o Arduino.
4. Configure as suas credenciais de nuvem para que os dados possam ser enviados e visualizados em uma dashboard.

## Utilização
1. Ligue o Arduino e os sensores e atuadores.
2. Verifique a dashboard para visualizar os dados em tempo real.
3. Ajuste os parâmetros de operação conforme necessário.

## Contribuição
Sinta-se livre para contribuir com este projeto enviando pull requests no Github.

## Licença
Este projeto está licenciado sob a licença GNU GPL v3. Consulte o arquivo [LICENSE.md](LICENSE.md) para obter mais detalhes.
