É um programa em linguagem C que implementa uma agenda de contatos simples, este programa opera diretamente com um arquivo de texto (Agenda_Contato.txt) para armazenar os dados e possui uma interface de linha de comando (terminal), com objetivo principal de criar um gerenciador de contatos baseado em terminal, permitindo ao usuário realizar operações básicas de uma agenda:

1.	Adicionar novos contatos (Nome e Telefone).

2.	Procurar contatos existentes por parte do nome.

3.	Mostrar todos os contatos salvos.

4.	Editar o telefone de um contato existente.

5.	Excluir um contato da agenda.

6.	Componentes Principais

7.	O programa é estruturado em funções que correspondem às opções do menu principal, e utiliza diretivas de pré-processador para compatibilidade entre sistemas operacionais (Windows/Linux) e modos de depuração.

•	Macros de Pré-processador (#ifdef, #define):

1.	ALERTA (msg): Define como exibir mensagens de alerta. No Windows, usa MessageBox; em outros sistemas (Linux), usa zenity (que abre uma caixa de diálogo gráfica).

2.	CLEAR_SCREEN(): Define como limpar a tela do terminal. No Windows, usa cls; em outros, clear. Se DEBUG for definido, não limpa a tela.

•	Métodos e Funcionalidades Essenciais

- Adicionar_contato():

1.	Entrada: Solicita o nome e o telefone do novo contato.

2.	Formatação de Telefone: Tenta formatar o número de telefone para o padrão (xx) xxxxx-xxxx. Se o formato digitado for inválido, salva como está e emite um alerta.

3.	Verificação de Duplicidade: Antes de adicionar, verifica se já existe um contato com o mesmo nome ou o mesmo número de telefone no arquivo. Se sim, exibe um alerta e impede a adição.

4.	Gravação: Adiciona o novo contato ao final do arquivo Agenda_Contato.txt no formato "Nome: [nome], Telefone: [telefone]".

- Procurar_Contato():

1.	Entrada: Solicita parte do nome do contato a ser procurado.

2.	Busca: Lê o arquivo linha por linha e verifica se a parte do nome digitada está contida no nome de algum contato existente.

3.	Exibição: Imprime os contatos encontrados no terminal.

- Mostrar_Contatos():

1.	Função: Lista todos os contatos armazenados no arquivo Agenda_Contato.txt.

2.	Exibição: Imprime cada linha do arquivo no terminal, precedida por um cabeçalho.

- Editar_Contato():

Entrada: Solicita o nome do contato que deseja editar e o novo telefone.

1.	Edição (Cópia e Substituição): Abre dois arquivos: o original para leitura e um temporário (Temp.txt) para escrita. Percorre o arquivo original, copiando as linhas para o arquivo temporário. Quando encontra o contato a ser editado, escreve a linha com o novo telefone no arquivo temporário.

2.	Substituição: Após processar todas as linhas, o arquivo original é removido e o temporário é renomeado para o nome do arquivo original, efetivando a edição.

- Excluir_contato_existente():

1.	Função: Permite remover um contato da agenda.

2.	Listagem Numerada: Primeiro, exibe todos os contatos numerados para que o usuário possa escolher qual excluir.

3.	Confirmação: Solicita o número do contato e pede uma confirmação (s/n) antes de realmente excluí-lo.

4.	Exclusão (Cópia e Omisssão): Similar à edição, usa um arquivo temporário. Copia todas as linhas para o arquivo temporário, exceto a linha correspondente ao contato a ser excluído.

- main():

1.	Ponto de Entrada: É a função principal do programa.
2.	Menu Interativo: Exibe um menu com as opções de adicionar, procurar, mostrar, editar, excluir e sair.

3.	Loop: Continua exibindo o menu e executando a função escolhida pelo usuário até que a opção de sair seja selecionada.

4.	getchar();: Usado após scanf para consumir o caractere de nova linha pendente, evitando problemas em leituras subsequentes.

•	Dependências:

1.	Compilador C: Necessita de um compilador C (como GCC) para ser compilado e executado.

2.	Para Alertas Gráficos (Linux): O comando zenity precisa estar instalado no sistema para que as caixas de diálogo de alerta funcionem.

3.	Sistema de Arquivos: Depende do sistema de arquivos para criar e manipular Agenda_Contato.txt e Temp.txt.
