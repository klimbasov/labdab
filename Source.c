#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#define ELEMENT_QUANTITY 80000
#define COLUMN_QUANTITY 8
#define RAW_QUANTITY 10000
#define ELEMENT_SIZE 4

unsigned long int * array, * result;


//unsigned long int benchmark(void (*)(unsigned long int*, unsigned long int*),size_t,int, unsigned long int*, unsigned long int*);
void set_array(unsigned long int*);
void show_result(const char*, unsigned long int);
void test_1(unsigned long int*, unsigned long int*);
void test_2(unsigned long int*, unsigned long int*);
void test_3(unsigned long int*, unsigned long int*);

int main() {
	LARGE_INTEGER start_counter, end_counter, frequency;
	QueryPerformanceFrequency(&frequency);
	array = (unsigned long int*)malloc((size_t)ELEMENT_QUANTITY * sizeof(unsigned long int));
	result = (unsigned long int*)calloc((size_t)COLUMN_QUANTITY , sizeof(unsigned long int));

	set_array(array);
	QueryPerformanceCounter(&start_counter);
	test_1(array, result);
	QueryPerformanceCounter(&end_counter);
	show_result("c result is", (end_counter.QuadPart - start_counter.QuadPart)*1000000 / frequency.QuadPart);
	free(result);
	result = (unsigned long int*)calloc((size_t)COLUMN_QUANTITY, sizeof(unsigned long int));
	QueryPerformanceCounter(&start_counter);
	test_2(array, result);
	QueryPerformanceCounter(&end_counter);
	show_result("MMX result is", (end_counter.QuadPart - start_counter.QuadPart)*1000000 / frequency.QuadPart);
	free(result);
	result = (unsigned long int*)calloc((size_t)COLUMN_QUANTITY, sizeof(unsigned long int));
	QueryPerformanceCounter(&start_counter);
	test_3(array, result);
	QueryPerformanceCounter(&end_counter);
	show_result("XMM result is", (end_counter.QuadPart - start_counter.QuadPart) * 1000000 / frequency.QuadPart);

}

void set_array(unsigned long int* array) {
	size_t counter = 0;
	while (counter < (size_t)ELEMENT_QUANTITY) {
		array[counter] = rand() % 10;
		++counter;
	}
}
void test_1(unsigned long int* array, unsigned long int* result) {
	size_t counter = 0;
	while (counter < (size_t)ELEMENT_QUANTITY) {
		result[counter%8] += array[counter];
		++counter;
	}
}
void show_result(const char* info_line, unsigned long int time) {
	size_t counter = 0;
	printf("%s [made in %u]:\n", info_line, time);
	while (counter < COLUMN_QUANTITY) {
		printf("%u\t", result[counter]);
		++counter;
	}
	printf("\n");
}
/*unsigned long int benchmark(void (*function_poiner)(unsigned long int*, unsigned long int*), size_t iterations, const short int time_format, unsigned long int* proc_array, unsigned long int* result_array) {
	size_t counter = 0;
	while (counter < iterations) {
		function_poiner
	}
}*/
void test_2(unsigned long int* array, unsigned long int* result){
	_asm {
		MOV EAX, array
		MOV EDX, (ELEMENT_QUANTITY-2)*4
		MOV EBX ,result
	LOOP_ENTRY:
		PADDD MM0, [EAX + EDX]
		PADDD MM1, [EAX + EDX - 8]
		PADDD MM2, [EAX + EDX - 16]
		PADDD MM3, [EAX + EDX -24]
		PADDD MM4, [EAX + EDX - 32]
		PADDD MM5, [EAX + EDX - 40]
		PADDD MM6, [EAX + EDX - 48]
		PADDD MM7, [EAX + EDX - 56]
		CMP EDX,56
		JZ CONTINUE
		SUB EDX, 64
		JMP LOOP_ENTRY
	CONTINUE:
		PADDD MM0, MM4
		PADDD MM1, MM5
		PADDD MM2, MM6
		PADDD MM3, MM7

		MOVQ [EBX], MM3
		MOVQ [EBX + 8], MM2
		MOVQ [EBX + 16], MM1
		MOVQ [EBX + 24], MM0
		EMMS
	}
}
void test_3(unsigned long int* array, unsigned long int* result) {
	_asm {
			MOV EAX, array
			MOV EDX, (ELEMENT_QUANTITY - 4) * 4
			MOV EBX, result
			XORPS XMM0, XMM0
			XORPS XMM1, XMM1
			XORPS XMM2, XMM2
			XORPS XMM3, XMM3
		LOOP_ENTRY :
			MOVUPS XMM4, [EAX + EDX]
			ADDPS XMM0, XMM4
			MOVUPS XMM5, [EAX + EDX - 16]
			ADDPS XMM1, XMM5
			MOVUPS XMM6, [EAX + EDX - 32]
			ADDPS XMM2, XMM6
			MOVUPS XMM7, [EAX + EDX - 48]
			ADDPS XMM3, XMM7
			
			CMP EDX, 48
			JZ CONTINUE
			SUB EDX, 64
			JMP LOOP_ENTRY
		CONTINUE :
			ADDPS XMM0, XMM2
			ADDPS XMM1, XMM3


			MOVUPS [EBX], XMM1
			MOVUPS[EBX+16], XMM0
			EMMS
	}
}

