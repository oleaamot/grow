/* -*- Mode: C; tab-width: 8; indent-tabs-mode: 8; c-basic-offset: 8 -*- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <config.h>

int main(int argc, char *argv[])
{
	FILE *fileno = NULL;
	long filepos = 0;
	long lastpos = 0;
	unsigned int usecs = 1000;
	if (argc > 1) {
		fileno = fopen(argv[1], "r");
		fseek(fileno, 1, SEEK_END);
		filepos = ftell(fileno);
		fprintf(stdout, "%s is %li bytes\n", argv[1], filepos - 1);
		while (1) {
			fclose(fileno);
			fileno = fopen(argv[1], "r");
			usleep(usecs);
			lastpos = (filepos - 1);
			fseek(fileno, 1, SEEK_END);
			filepos = ftell(fileno);
			if ((filepos - 1) > (lastpos)) {
				fprintf(stdout, "%s is %li bytes\n", argv[1],
					filepos - 1);
				lastpos = (filepos - 1);
			}
			if (argc > 2) {
				if ((filepos - 1) == atol(argv[2])) {
					return (0);
				}
				if ((filepos - 1) > atol(argv[2])) {
					fprintf(stdout,
						"%s is %li bytes (%li bytes larger)\n",
						argv[1],
						(filepos - 1),
						(filepos - 1) - atol(argv[2]),
						atol(argv[2]));
					return (0);
				}
				if ((filepos - 1) < atol(argv[2])) {
					if ((filepos - 1) == lastpos) {
					}
				}
			}
		}
		return (0);
	} else {
		fprintf(stdout, "%s %s\n", PACKAGE, VERSION);
		fprintf(stdout, "Copyright (C) 2012-2014 Ole Aamot\n\n");
		fprintf(stdout, "Usage: %s FILE BYTESIZE\n", PACKAGE);
	}
	return (0);
}
