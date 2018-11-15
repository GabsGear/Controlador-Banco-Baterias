# Controlador-Banco-Baterias


### Trabalho final Microcontroladores e Microprocessadores
#### Sistema para otimização de carga e descarga de bancos de bateria implementado com o controlador PIC 16f877A.

#### Requisitos:

A seleção e a manutenção da tensão específica de carga e flutuação são essenciais para alcançar a vida útil e capacidade projetada da bateria. Se a tensão de carga e flutuação for muito alta causará crescimento acelerado e corrosão da placa reduzindo a vida útil da bateria. Se a tensão de carga e flutuação for muito baixa, a bateria não será mantida a plena carga, isto
causará sulfatação das placas resultando na degradação da capacidade e redução da vida útil. As baterias estacionárias Freedom podem ser mantidas à plena carga se permanentemente ligadas a uma fonte de carga de flutuação entre 13,2 e 13,8 Volts @ 25°C. Porém salientamos que todas as vezes que forem submetidas a uma descarga é obrigatório que sejam recarregadas de acordo com o especificado no item 3.4 sempre fazendo a correção de tensão de acordo com a temperatura.
As tensões de equalização e flutuação devem ser ajustadas em função da temperatura de acordo com a tabela abaixo.
Em algumas ocasiões as baterias estarão expostas a variações de temperatura, neste caso pode-se adotar uma temperatura média para tensão de carga e flutuação. 


### Seguem os requisitos para carga seguindo o manual da bateria [Freedon](http://www.logik.com.br/download/ManualTecnicoBateriasFreedom.pdf)

+  ***Item 3.3 Instruções de carga:***
    Tensão de flutuação: 13,2 a 13,8 V @ 25°C (Para carga constante como no breaks)
    Tensão de equalização e carga: 14,4 a 15,5 V @ 25°C (Carga eventual um ciclo de carga)
+  ***Item 3.4  Compensação de temperatura:*** 
    Para cada 1°C acima de 25°C, subtrair 0,033 V e para cada 1°C abaixo de 25°C, adicionar
    0,033 V. 
+ ***Item 3.5 Vida útil:***  
    A temperatura do ambiente de operação da bateria deve sempre estar entre –10ºC e 45ºC, portando o controlador terá que emitir um aviso quando tais temperaturas forem atingidas.

+ ***O controlador deve*** ter duas opções de carga, flutuação ou equalização.

### Requisitos sistema de descarga
+ ***Sempre que houverem descargas*** o uso do banco de baterias deve ser otimizado para que todos os circuitos recebam alimentação por um maior período de tempo até a descarga de todas as baterias.


#### Hardware:
![IMG1](https://github.com/GabsGear/Controlador-Banco-Baterias/blob/master/HARDWARE/proc_ind.jpeg)
