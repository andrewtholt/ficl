/*
** stub main for testing Ficl
** $Id: //depot/gamejones/ficl/main.c#2 $
*/
/*
** Copyright (c) 1997-2001 John Sadler (john_sadler@alum.mit.edu)
** All rights reserved.
**
** Get the latest Ficl release at http://ficl.sourceforge.net
**
** I am interested in hearing from anyone who uses Ficl. If you have
** a problem, a success story, a defect, an enhancement request, or
** if you would like to contribute to the Ficl release, please
** contact me by email at the address above.
**
** L I C E N S E  and  D I S C L A I M E R
** 
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>

#include "ficl.h"

ficlVm *f_vm;
ficlSystem *f_system;

#include <signal.h>

int signals[] = {
#ifdef SIGQUIT
	SIGQUIT,
#endif
#ifdef SIGILL
	SIGILL,
#endif
#ifdef SIGABRT
	SIGABRT,
#endif
#ifdef SIGFPE
	SIGFPE,
#endif
#ifdef SIGSEGV
	SIGSEGV,
#endif
#ifdef SIGBUS
	SIGBUS,
#endif
#ifdef SIGSYS
	SIGSYS,
#endif
#ifdef SIGTRAP
	SIGTRAP,
#endif
#ifdef SIGXCPU
	SIGXCPU,
#endif
#ifdef SIGXFSZ
	SIGXFSZ
#endif
};

jmp_buf mainLoop;

static void sig_handler(int sig)
{
	if (SIG_ERR == signal (sig, sig_handler)) {
		sprintf(f_vm->pad, "Error: signal reinstall failed\n");
		ficlVmErrorOut(f_vm, f_vm->pad);
	}
	longjmp (mainLoop, sig);
}

static void install_handlers(void)
{
	int i;

	for (i = 0; i < sizeof(signals) / sizeof(int); i++) {
		signal (signals[i], sig_handler);
	}
}

static void usage()
{
	fprintf(stderr,"usage: ficl [-sN] [-dN] [-eN] [file1 file2 ...]\n");
	exit(1);
}

int main(int argc, char **argv)
{
   int returnValue = 0;
   char buffer[256];
	int sig;
	int done;
	int narg;
	ficlSystemInformation fsi;

	install_handlers();
	ficlSystemInformationInitialize(&fsi);

	narg = 1;
	while ((narg < argc) && ('-' == *argv[narg])) {
		switch (argv[narg][1]) {
		case 's': fsi.stackSize = atoi(argv[narg]+2); break;
		case 'e': fsi.environmentSize = atoi(argv[narg]+2); break;
		case 'd': fsi.dictionarySize = atoi(argv[narg]+2); break;
		default:	 usage();
		}
		narg++;
	}

   f_system = ficlSystemCreate(&fsi);
   ficlSystemCompileExtras(f_system);
   f_vm = ficlSystemCreateVm(f_system);

   returnValue = ficlVmEvaluate(f_vm, ".ver .( " __DATE__ " ) cr quit");

   /*
   ** load files specified on command-line
   */
	while (narg < argc) {
		sprintf(buffer, ".( loading %s ) cr load %s\n cr", argv[narg], argv[narg]);
		returnValue = ficlVmEvaluate(f_vm, buffer);
		narg++;
	}

	if (sig = setjmp(mainLoop)) {
		sprintf(f_vm->pad, "Error: got signal (%d)\n", sig);
		ficlVmErrorOut(f_vm, f_vm->pad);
	}

	done = 0;
    /* while (returnValue != FICL_VM_STATUS_USER_EXIT) */
	while (!done)
	{
		fputs(FICL_PROMPT, stdout);
		fgets(buffer, sizeof(buffer), stdin);
		returnValue = ficlVmEvaluate(f_vm, buffer);
		switch (returnValue) {
		case FICL_VM_STATUS_OUT_OF_TEXT:
		case FICL_VM_STATUS_ERROR_EXIT:
			break;
		case FICL_VM_STATUS_USER_EXIT:
			done = 1;
			break;
		default:
			sprintf(f_vm->pad, "Error: got exception (%d)\n", returnValue);
			ficlVmErrorOut(f_vm, f_vm->pad);
			break;
		}
    }

    ficlSystemDestroy(f_system);
    return 0;
}

