#include "../../headers/minishel.h"


//fix values !!!!!!



int main(int argc, char **argv, char **envp)
{
	t_tokens tok;
	t_vars *head_ex;
	t_vars *head_env;

	(void)argc;
	(void)argv;

	head_ex = NULL;
	head_env = NULL;
	env_list_init(&head_ex, envp);
	env_list_init(&head_env, envp);
	export("var=pupu", &head_ex, &head_env);
	export("a=file.txt", &head_ex, &head_env);
	export("c=>", &head_ex, &head_env);

	export("?=EXIT_CODE", &head_ex, &head_env);

	init_parsing_struct(&tok);
	char *line = "echo $var > $a > file2.txt >file3.txt";

	// "\"$$$$USER''\"" - segfault
	// "\"$$$$USER'\"" - no token
	// "echo '>>' " - three tokens instead of two

	// "echo $$$$$abc abc";
	
	// "'$assads'" - fixed seg fault but still...
	

	// FIXED  	"echo >>><< abc < def >fuck > you" - broken redirection is one token for some reason
	// FIXED	variable on the first place - valgrind errors
	// FIXED	"echo '|' abc < def >fuck > you" - splitted by pipe (should not)
	
	
	char **lines;
	int a = 0;

	lines = split_pipes(&tok, line);
	while (lines[a])
	{
		printf("begin:\n");
		printf("%s\n", lines[a]);
		printf("\n");

		char *line2 = first_expand(&tok, head_ex, lines[a]);
		printf("first expand:\n");
		printf("%s\n", line2);
		printf("\n");

		puts("after first expand");

		char **tokens = make_token(&tok, line2);
		int i = 0;
		free(line2);

		if (!tokens)
			return (0);

		printf("tokens:\n");
		while (tokens[i])
		{
			printf("%d: %s\n", i, tokens[i]);
			//free(tokens[i]);
			i++;
		}
		//free(tokens);
		printf("\n");

		//return(1);
		
		i = 0;	
		char **fin = last_expand(&tok, head_ex);
		if (!fin)
			return (0);

		//rereplace_redirect(&tok);

		printf("last expand\n");
		while (fin[i])
		{
			printf("%d: %s\n", i,  fin[i]);
			//free(fin[i]);
			i++;
		}
/* 		printf("%d: %s\n", i,  fin[i]);
		i++;
		printf("%d: %s\n", i,  fin[i]); */
		//free(fin);

		puts("pup");

		t_redirect redirect_lst;
		t_cmd	cmd_lst;
		t_shell shell;

		redirect_lst.type = 0;
		redirect_lst.file_name = NULL;
		redirect_lst.del_flag = 0;
		redirect_lst.nest = NULL;

		cmd_lst.path = NULL;
		cmd_lst.cmd = NULL;
		cmd_lst.args = NULL;
		cmd_lst.redirect_lst = redirect_lst;
		cmd_lst.next = NULL;

		shell.cmd_lst = cmd_lst;
		shell.last_exit_code = 0;
		shell.




		puts("ööö");

		cmd_lst->redirect_lst = NULL;

		puts("****");

		classifiying_tokens(&tok, cmd_lst.redirect_lst, &cmd_lst);
		//classifiying_tokens(&tok, &shell.cmd_lst);


		i = 0;
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);

		i = 0;
		while (fin[i])
		{
			free(fin[i]);
			i++;
		}
		free(fin);

		a++;
	}

/* 	printf("head ex\n");
	export(NULL, &head_ex, &head_env); */

	clear_list_env(&head_env);
	clear_list_env(&head_ex);

}
