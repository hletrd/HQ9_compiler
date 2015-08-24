#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
	stdout = NULL;
	if (access(argv[1], F_OK) != -1 && strlen(argv[2]) > 0) {
		fprintf(stdout, "Compiling %s\n\n", argv[1]);

		FILE *fp = fopen(argv[1], "r");
		fseek(fp, 0, SEEK_END);
		int filesize = ftell(fp);
		fclose(fp);

		char *inp = (char*)malloc(filesize+1);
		int i;

		freopen(argv[1], "r", stdin);
		FILE *out_c = fopen("converted.c", "w");
		fprintf(out_c, "#include <stdio.h>\n");
		fprintf(out_c, "#define beers bottles = 99; do { printf(\"%%d bottles of beer on the wall\\n\", bottles); printf(\"%%d bottles of beer\\n\", bottles); printf(\"Take one down, pass it around\\n\"); printf(\"%%d bottles of beer on the wall\\n\\n\", --bottles);} while(bottles > 0);\n");
		fprintf(out_c, "int bottles = 0;\n");
		fprintf(out_c, "char *helloworld = \"Hello, world!\";\n");
		fprintf(out_c, "char *source = \"");
		while((inp[i] = getchar()) != EOF){
			if (inp[i] == '\n' && i == filesize-1);
			else if (inp[i] == '"') fprintf(out_c, "\\\"");
			else if (inp[i] == '\n') fprintf(out_c, "\\n");
			else if (inp[i] == '\r') fprintf(out_c, "\\r");
			else fprintf(out_c, "%c", inp[i]);
			i++;
		}
		inp[i-1] = 0;
		fprintf(out_c, "\";\n");
		fprintf(out_c, "int main(int argc, char *argv[]) {\n");
		
		for(int j = 0; j < i-1; j++) {
			if (inp[j] == 'H') {
				fprintf(out_c, "\tputs(helloworld);\n");
			} else if (inp[j] == 'Q') {
				fprintf(out_c, "\tputs(source);\n");
			} else if (inp[j] == '9') {
				fprintf(out_c, "\tbeers\n");
			}
		}
		fprintf(out_c, "}");
		fclose(out_c);
		char buf[10000];
		sprintf(buf, "gcc -O2 -o %s converted.c", argv[2]);
		system(buf);
		return 0;
	} else {
		fprintf(stderr, "Input file not found.\nUsage: hq9+c input.hq output.out\n(Code will always be highly optimized.)\n\nHQ9+ to C compiler 0.0.1 by HLETRD\n\nDependency: gcc\n");
		return 1;
	}
}