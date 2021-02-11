; Text coding by one-time pad code or Vigenere code, version 0.0
; Author: Sara Witek
; Subject: Jezyki Assemblerowe
; Year: 2020 / 2021
; Compiler: MASM
; File containing one-time coding and Vigenere coding algorithms.
; The main idea of the algorith is : Depending from the input text and the automatic genereted password, text is being coded.
; There is two ways how the password can be genereted by one-time coding or by Vigenere coding. 
; One-time coding means that password is shorter than whole text and it loops to code the text
; Vigenere coding password is in the same size like the text and it is tottaly random.
; The order:
; Calculate the displacement of the character from text
; Add the displacement from password
; Checking what character is going to represent coded character - modulo operation due to 35 available characters
; Setting back again ASCII position
; All operations available for capital and lower letters, different letters are rewritten

.data
   sizeoffile DWORD 0               ; Declaring sizeoffile for 0
.code

asmTextCoding proc
;   rcx - Pointer to the beginning of the password array displacement for particular thread
;   rdx - Pointer to the beginning of the text array for particular thread
;   r8 - Pointer to the beginning of the text displacement array for particular thread
;   r9 - Pointer to the beginning of the output array
;   On stack - Size of the part of file, which is executed by particular thread
 
    mov     eax,[rsp+40]              ; Move value from the stack to the eax
    mov     sizeoffile,eax            ; Move eax to sizeoffile

	push    rbp					      ; Save address of previous stack frame
	push    rdi					      ; Save register destination index
	push    rsp					      ; Save stack pointer

    cmp     sizeoffile,0              ; Checking if there is at least one byte in the array 
    jle     @Finished                 ; If not jump to @Finished
    
    xor     r10,r10                   ; Set r10 to 0, setting offset pointer
    mov     eax,sizeoffile            ; Move value of sizeoffile to eax
    shr     eax,3                     ; Divide the byte count by 8
    cmp     eax,0                     ; Make sure that there is at least 8 byte to copy
    je      @NoMMX                    ; If not, the array is too small to use MMX
 
@MMXLoop:
    movq    mm0,qword ptr [rcx+r10]   ; Copy 8 bytes from password array displacement into mm0 ;
    movq    mm1,qword ptr [rdx+r10]   ; Copy 8 bytes from text array into mm1 ; 
    movq    mm2,qword ptr [r8+r10]    ; Copy 8 bytes from text displacement array into mm2 ;

    mov     ebx,34                    ; Move 34 to ebx
    movd    mm5,ebx                   ; Copy ebx to the low dword of mm5, movd clears the top of mm5 to zeros
    punpckldq mm5,mm5                 ; Copies the low 32 bits to the top
    packssdw  mm5,mm5                 ; Chopped the dwords into words
    packsswb  mm5,mm5                 ; Chopped the words into bytes
        
    mov   ebx,1                       ; Move 1 to ebx
    movd  mm6,ebx                     ; Copy ebx to the low dword of mm6, movd clears the top of mm6 to zeros
    punpckldq mm6,mm6                 ; Copies the low 32 bits to the top
    packssdw  mm6,mm6                 ; Chopped the dwords into words 
    packsswb  mm6,mm6                 ; Chopped the words into bytes

    ; Modulo operation due to 35 available characters - checking what character is going to represent coded character
    psubb   mm1,mm2                   ; Calculate displacement for character from text
    paddb   mm1,mm0                   ; Movement to the right according to the password displacement
    movq    mm4,mm1                   ; Copy the text array to mm4
    pcmpgtb mm4,mm5                   ; Checking which character displacement is greater than 34
    paddb   mm5,mm6                   ; Add 1 to create vector full of number '35'
    pand    mm4,mm5                   ; Creating the modulo vector, only place of character which displacement is higher than 34 is filled by 35
    psubb   mm1,mm4                   ; Substraction only for characters which displacement is higher than 34
    paddb   mm1,mm2                   ; Setting back to the ASCII position
    movq    qword ptr[r9+r10],mm1     ; Write that sign to the right place in output array ;[r9+r10]
    add     r10,8                     ; Move offset pointer to the next 8 bytes
    dec     eax                       ; Dec the counter (r10 is in this loop)
    jnz     @MMXLoop                  ; If there is more, jump back again to the MMXLoop

@NoMMX:                               ; There less then 8 bytes, it has to be check how much left
    mov     eax,sizeoffile            ; Put back the original size of eax
    shr     eax,3                     ; Divide by 8
    shl     eax,3                     ; Multiply by 8            
    sub     sizeoffile,eax            ; Calculation of the numbers of bytes left to do.    
    cmp     sizeoffile,0              ; Checking if MMXLoop hasn't finished the all bytes
    jz      @Finished                 ; If it did, move to @Finished

@ResidualLoop:                        ; Rest bytes of array to code
    mov     al,byte ptr [rdx+r10]     ; Move byte from text array to al
    sub     al,byte ptr [r8+r10]      ; Substract from al the displacement for that sign
    add     al,byte ptr [rcx+r10]     ; Add to al the password value 
    sub     al,35                     ; Substract 35 - modulo 35
    cmp     al,0                      ; Check if the al is below 0
    jge     @Ready                    ; Value of the sign was above or equal to 35 correct modulo was done
    add     al,35                     ; Correction modulo because value was below 35

@Ready:
    add     al,byte ptr [r8+r10]      ; Add back the displacement for that sign
    mov     byte ptr [r9+r10],al      ; Move the coded sign to the output array 
    inc     r10                       ; Move onto the next byte
    dec     sizeoffile                ; Decrement our counter
    jnz     @ResidualLoop             ; Jump if we have more to copy

@Finished:						      ; End of loop while
	pop rsp						      ; Return rsp from stack
	pop rdi						      ; Return rdi from stack 
	pop rbp						      ; Return rbp from stack
	mov eax, 0					      ; Function always works and always returns 0
	ret							      ; Return from function

asmTextCoding endp

asmTextUncoding proc
;   rcx - Pointer to the beginning of the password array displacement for particular thread
;   rdx - Pointer to the beginning of the text array for particular thread
;   r8 - Pointer to the beginning of the text displacement array for particular thread
;   r9 - Pointer to the beginning of the output array
;   On accumulator - Size of the part of file, which is executed by particular thread
 
    mov     eax,[rsp+40]              ; Move value from the stack to the eax
    mov     sizeoffile,eax            ; Move eax to sizeoffile

	push    rbp					      ; Save address of previous stack frame
	push    rdi					      ; Save register destination index
	push    rsp					      ; Save stack pointer

    cmp     sizeoffile,0              ; Checking if there is at least one byte in the array to copy
    jle     @Finished                 ; If not jump to @Finished
    
    xor     r10,r10                   ; Set r10 to 0, setting offset pointer
    mov     eax,sizeoffile            ; Move value of sizeoffile to eax
    shr     eax,3                     ; Divide the byte count by 8
    cmp     eax,0                     ; Make sure that there is at least 8 byte to copy
    je      @NoMMX                    ; If not, the array is too small to use MMX
 
@MMXLoop:
    movq    mm0,qword ptr [rcx+r10]   ; Copy 8 bytes from password array displacement into mm0 ;
    movq    mm1,qword ptr [rdx+r10]   ; Copy 8 bytes from text array into mm1 ; 
    movq    mm2,qword ptr [r8+r10]    ; Copy 8 bytes from text displacement array into mm2 ;
    
    mov     ebx,0                     ; Move 0 to ebx
    movd    mm5,ebx                   ; Copy ebx to the low dword of mm5, movd clears the top of mm5 to zeros
    punpckldq mm5,mm5                 ; Copies the low 32 bits to the top
    packssdw  mm5,mm5                 ; Chopped the dwords into words
    packsswb  mm5,mm5                 ; Chopped the words into bytes
     
    mov   ebx,35                      ; Move 35 to ebx
    movd  mm6,ebx                     ; Copy ebx to the low dword of mm6, movd clears the top of mm6 to zeros
    punpckldq mm6,mm6                 ; Copies the low 32 bits to the top
    packssdw  mm6,mm6                 ; Chopped the dwords into words 
    packsswb  mm6,mm6                 ; Chopped the words into bytes

    ; Modulo operation due to 35 available characters - checking what character is going to represent coded character
    psubb   mm1,mm2                   ; Calculate displacement for character from text
    psubb   mm1,mm0                   ; Movement to the right according to the password displacement
    movq    mm4,mm1                   ; Copy the text array to mm4
    movq    mm0,mm1                   ; Copy the text array to mm0
    pcmpgtb mm4,mm5                   ; Checking which character is above 0
    pcmpeqb mm0,mm5                   ; Checking which character is equal to 0
    por     mm4,mm0                   ; OR of mm4 and mm0, which character are above or equal to 0
    pcmpeqb mm5,mm5                   ; Creating mm5 which has each byte as 11111111
    pxor    mm4,mm5                   ; XOR mm4,mm5 to get the character which are below 0
    pand    mm4,mm6                   ; Creating the vector, only place of character where the value was below 0 is filled
    paddb   mm1,mm4                   ; Adding only for characters which displacement is higher than 34
    paddb   mm1,mm2                   ; Setting back to the ASCII position
    movq    qword ptr[r9+r10],mm1     ; Write that sign to the right place in output array ;[r9+r10]
    add     r10,8                     ; Move offset pointer to the next 8 bytes
    dec     eax                       ; Dec the counter (r10 is in this loop)
    jnz     @MMXLoop                  ; If there is more, jump back again to the MMXLoop

@NoMMX:                               ; There less then 8 bytes, it has to be check how much left
    mov     eax,sizeoffile            ; Put back the original size of eax
    shr     eax,3                     ; Divide by 8
    shl     eax,3                     ; Multiply by 8            
    sub     sizeoffile,eax            ; Calculation of the numbers of bytes left to do.    
    cmp     sizeoffile,0              ; Checking if MMXLoop hasn't finished the all bytes
    jz      @Finished                 ; If it did, move to @Finished

@ResidualLoop:                        ; Rest bytes of array to code
    mov     al,byte ptr [rdx+r10]     ; Move byte from text array to al
    sub     al,byte ptr [r8+r10]      ; Substract from al the displacement for that sign
    sub     al,byte ptr [rcx+r10]     ; Substract to al the password value 
    cmp     al,0                      ; Check if the value is below 0
    jge     @Ready                    ; If the value if above or equal to 0 - no correction needed
    add     al,35                     ; Add 35, because value was lower than 35 - only that many letters avaiable
@Ready:
    add     al,byte ptr [r8+r10]      ; Add back the displacement for that sign
    mov     byte ptr [r9+r10],al      ; Move the coded sign to the output array 
    inc     r10                       ; Move onto the next byte
    dec     sizeoffile                ; Decrement our counter
    jnz     @ResidualLoop             ; Jump if we have more to copy

@Finished:						      ; End of loop while
	pop rsp						      ; Return rsp from stack
	pop rdi						      ; Return rdi from stack 
	pop rbp						      ; Return rbp from stack
	mov eax, 0					      ; Function always works and always returns 0
	ret							      ; Return from function

asmTextUncoding endp
end

