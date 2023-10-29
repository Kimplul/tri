#include <tdump/disassembler.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static const char *cmdline_usage =
"tdump trinary deassembler usage:\n"
" tdump infile\n"
"	-h     Show usage (this)\n"
"	infile File to deassemble\n"
;

static void usage()
{
	fprintf(stderr, cmdline_usage);
}

int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
		case 'h':
			usage();
			exit(EXIT_SUCCESS);
			break;

		default:
			usage();
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "no input files\n");
		usage();
		exit(EXIT_FAILURE);
	}

	if (optind != argc - 1) {
		fprintf(stderr, "too many input files\n");
		usage();
		exit(EXIT_FAILURE);
	}

	if (disassemble(argv[optind]))
		exit(EXIT_FAILURE);

	return EXIT_SUCCESS;
}
