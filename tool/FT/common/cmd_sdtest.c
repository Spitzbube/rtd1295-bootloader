#include <common.h>
#include <command.h>
#include <sd_test.h>


static int parse_argv(const char *);

int do_sdtest ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	
	switch (argc) {
	case 2:			
		switch (parse_argv(argv[1])) 
		{
		case 0:	sd_test_0();
			break;		
		case 1:	sd_test_1();
			break;
		case 2:	sd_test_2();
			break;
		case 3: sd_test_3();
			break;
		}
		return 0;
		/* FALL TROUGH */
	case 1:			/* get status */
		printf ("Run default: sd test code #0\n\n\n");	
		sd_test_0();
		return 0;
	default:
		return CMD_RET_USAGE;
	}
	return 0;

}

static int parse_argv(const char *s)
{
	if (strcmp(s, "0") == 0) {
		return (0);
	} else if (strcmp(s, "1") == 0) {
		return (1);
	} else if (strcmp(s, "2") == 0) {
		return (2);
	} else if (strcmp(s, "3") == 0) {
		return (3);	
	}
	return (-1);
}


U_BOOT_CMD(
	test,   2,   1,     do_sdtest,
	"run sd test code",
	"test code 0, 1, 2, 3.........\n"
	"    run sd test code"
);
