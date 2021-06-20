#include <stdio.h>
//mikro.c
//c routine for get_hash
int get_hash2(char* a, int* hashTable);
/*
r0 -> the char pointer passed in through function arguments
r1 -> the pointer to hashTable passed in through function arguments
r2 -> destination in memory of the hash
r3 -> has the temp character that we check

*/
__asm int get_hash(char*src,int* hshTable, int *dst){
		PUSH {r4,r5,r6,r7}   // reserve space for r4,r5,r6,r7 registers in stack
		MOV  r4,#0        //initialize r4 to 0 -> hash = 0 
		MOV  r5,#0				//initialize r5 to 0 -> hashKey_index
		MOV  r7,#0        //initialize r7 to 0 -> hashTable_value
		MOV  r6,#4        //initialize r6 to 4  -> multiplier for integer_indexing (4 bytes)
loop 
		LDRB r3, [r0]   //load the tempCar from r0
		ADD r0, #1     //increase r0 1 byte (sizeOf(char))
		CMP  r3,#0      //check if we have the terminal character of the string = '\0'
		BEQ  exit				// if equal branch to exit label
		CMP  r3, #'A'-1    //compare (first if statement first condition)ASCII integer representation of tempCar with 64 ('A'- 1)
		BLS  condNum    //if less branch to condNUM tag(second if statement)
		CMP  r3, #'Z'+1    //compare ASCII integer representation of tempCar with 91 ('Z' + 1)
		BHI  loop       // if its higher loop -> continue
		SUB r5,r3,#'A'  //inside first if // map the Capital Character A-Z to the hashTable with r5=hashKey_index
		MUL  r5,r5,r6   // multiply r5 with r6 cause r5 index points to integer (4 bytes)
		LDRB r7, [r1, r5] // load the byte from hashTable in index = hastTable_index
		ADD  r4,r4,r7     // hash = hash + hashTable[hashKey_index]
		STR  r4,[sp]      // store value to sp (in order to return it to r0)
		B 	 loop		
condNum // second if 
		CMP r3,#'9'+1   //first condition of 2nd if 
		BHI loop     //case its not fulfilled branch to loop
		CMP r3,#'0'-1   //second condition of 2nd if 
		BLS loop 		 //case its not fulfilled branch to loop
		SUB r4,r4,r3  // hash-(int)tempChar //(int)tempChar starts from 48 and ends at 58  (0 - 9) ASCII repressentation
		ADD r4,#'0'   // add 48 in order to map integer part of char (0->0 and not 0->-48)
		STR r4,[sp]   //store r4 to sp (in order to return it to r0)
		B loop        
		
exit 
		LDR r0,[sp]   // load from sp the returned value(r3) to r0
		STR r4,[r2]    // store hash to memeory address that r2 points
		POP {r4,r5,r6,r7} // free reserved registers
		BX  lr         // branch to link_Register
}

//The main has test strings that we tried out.
int main(){
		/*Given string*/
		//char* a[] = 
//		char a[] = "!!# ";												//problem when with others alone works fine return hash = 0
    char b[]= "Ar, PE 2!Bb ";										//checked
//	  char b[] = "123456789 ";                   //checked
//	  char d[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";   //checked 
    int hashTable[]={18, 11, 10, 21, 7, 5, 9, 22, 17, 2, 12, 3, 19, 1, 14, 16, 20, 8, 23, 4, 26, 15, 6, 24, 13, 25};
		int *hash_dst = 0;
		int hash_b;
//		hash_a = get_hash(a, hashTable);
		hash_b = get_hash(b,hashTable,hash_dst);
//		hash_c= get_hash(c,hashTable);
//		hash_d= get_hash(d,hashTable);		
//		if(hash_a == get_hash2(a,hashTable) && hash_b == get_hash2(b,hashTable) && hash_c == get_hash2(c,hashTable) && hash_d == get_hash2(d,hashTable)){
//			return 1;
//		}

		if(hash_b == get_hash2(b,hashTable)){
			return 1;
		}
    return 0;
}



//c code for get hash named get_hash2 for avoiding function multireferencing.
int get_hash2(char* a, int* hashTable){
    int str_index=0;
    int hashKey_index=0;                   //Initialising with this value, and we map 'A' in ASCII(integer  counterpart) to hashTable_indexing 
    int hash = 0;
		char tempChar;

    while(a[str_index]!='\0'){
        tempChar=a[str_index];
        //Case of a capital letter
        if(tempChar>64 && tempChar<91){
            hashKey_index=(int)tempChar-65;          //With the (int) typecasting I get the ASCII counterpart of the character
            hash=hash+hashTable[hashKey_index];
        }

        //Case of a number
        else if(tempChar>47 && tempChar<58){            
            hash=hash-(int)tempChar+48;
        }
        str_index++;
    }
    return hash;
}
