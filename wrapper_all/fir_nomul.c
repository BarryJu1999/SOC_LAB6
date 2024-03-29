#include "fir.h"

void __attribute__ ( ( section ( ".mprjram" ) ) ) initfir() {
	for(int i=0; i<N; i++) {
		inputbuffer[i] = 0;
		outputsignal[i] = 0;
	}
}

int __attribute__ ( ( section ( ".mprjram" ) ) ) firfilter(int inputsample){
	for(int i=N-1; i>0; i--){
		inputbuffer[i] = inputbuffer[i-1];
	}
	inputbuffer[0] = inputsample;
	int outputsample = 0;
	for(int i=0; i<N; i++){
		int mulresult = 0;
		for (int j=0; j<inputbuffer[i]; j++){
			mulresult = mulresult + taps[i];
		}
		outputsample = mulresult + outputsample;
	}
	return outputsample;
}

int* __attribute__ ( ( section ( ".mprjram" ) ) ) fir(){
	initfir();
	for(int i=0; i<N; i++){
		outputsignal[i] = firfilter(inputsignal[i]);
	}
	return inputsignal;
}
		
