# projeto_eletricidade_I
Este projeto é um programa em linguagem C que realiza a simulação de um circuito RLC série (resistor, indutor e capacitor) com base nos parâmetros fornecidos pelo usuário. O foco está em determinar o tipo de amortecimento do circuito e calcular grandezas características do sistema dinâmico.
Funcionalidades principais:

Solicita ao usuário:
Nome
Valores e unidades de resistência (R), indutância (L), capacitância (C)
Tensão inicial no capacitor (V₀)
Corrente inicial no indutor (I₀)
Converte unidades de entrada para o Sistema Internacional.

Calcula:
Frequência natural não amortecida (ω₀)
Constante de amortecimento (σ)
Frequência amortecida (ω_d), quando aplicável
Corrente inicial no capacitor (I_C₀)

Determina o tipo de amortecimento do circuito:
Subamortecido (oscilações decaem)
Criticamente amortecido (retorna ao equilíbrio rapidamente, sem oscilações)
Superamortecido (retorno lento, sem oscilações)
Para cada tipo, calcula os coeficientes da solução da equação diferencial e o tempo/tensão do pico máximo (quando aplicável).

Autores:
Camila Nobrega
Thaynara Magno

Objetivo educacional:
Esse programa auxilia no estudo de circuitos RLC transitórios, reforçando conceitos como amortecimento, resposta natural e uso de unidades no contexto da engenharia elétrica e da computação.

