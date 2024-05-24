/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#include <tasm/assembler.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static const char *cmdline_usage =
	"tasm trinary assembler usage:\n"
	" tasm [-I <dir>...] -o outfile infile\n"
	"	-h           Show usage (this)\n"
	"	-I <dir>     Add directory to include path\n"
	"	-o <outfile> File to output to\n"
	"	infile       Top file to assemble\n"
;

static void usage()
{
	fprintf(stderr, cmdline_usage);
}

int main(int argc, char *argv[])
{
	const char *outfile = NULL;
	int opt;
	while ((opt = getopt(argc, argv, "hI:o:")) != -1) {
		switch (opt) {
		case 'I':
			fprintf(stderr, "include paths not yet implemented\n");
			break;

		case 'o':
			outfile = optarg;
			break;

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

	if (!outfile || strlen(outfile) == 0) {
		fprintf(stderr, "no output file\n");
		usage();
		exit(EXIT_FAILURE);
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

	if (assemble(outfile, argv[optind]))
		exit(EXIT_FAILURE);

	return EXIT_SUCCESS;
}
