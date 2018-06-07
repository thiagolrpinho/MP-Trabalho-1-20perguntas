# Trabalho 4 

Seja bem-vindo(a) à parte 4 do projeto de métodos de programação do jogo de 20 perguntas.

## Gcov

Os teste do Gcov foram refeitos para os métodos da biblioteca stringnode.hpp e btree.hpp para que atingissem máxima cobertura.
Para vê-los, basta acessar a pasta tests/gcov/ e abrir o arquivo
*tests-detailts.html*

## Fluxograma dos Testes de Decisões
Todos os métodos da strignode.hpp e da btree.hpp que possuíam decisões booleanas foram representados em fluxogramas. Os que possuíam somente uma decisão e, consequentemente, só teriam uma letra associada a ela foram omitidas as letras. Elas se encontram na pasta Trabalho 4/fluxogramas

## Testes de caminhos
Os testes de caminhos foi feito em somente um método Stringnode::cutNode(), o único que possuía mais de uma decisão booleana. Ele foi amplamente testado no arquivo *tests_btree.cpp* que pode ser encontrado na pasta /tests/. Há um caso de testes somente para esse método, lá é explicado como os testes foram construídos usando cobertura de caminhos.

## Tabela de Decisão
A tabela de decisão se encontra nessa mesma pasta /Trabalho 4/ no arquivo chamado *tabela_de_decisoes.pdf*

### Autoria
Feito por Thiago Luis Rodrigues Pinho - Matrícula na Unb 15/0065205
Data: 06-06-2018


*Agradeço aos meus colegas que me deram suporte, ao professor que me orientou e a todos aqueles que puderam ler esse texto e me ajudar a melhorar.*