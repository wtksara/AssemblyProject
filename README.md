# AssemblyProject
First project, which combined C++ and Assembly. Topic of the project "Coding and uncoding by Viegenere code or one-time pad". GUI let user to choose the way of the coding, DLL library ( C++ or ASM) and the number of threads. There is already prepered .txt files for different size of data. 

## GUI
After starting the program, the user can only choose whether he intends to encrypt or decrypt the text. All other possibilities are blocked for functional reasons.

<img src="/gui.png">

If you want to encrypt the text, the user can choose the type of cipher, library and the method of multithreading. The program offers two types of cipher: one-time and Vigenere, a detailed description and differences are presented in the description of the encoding algorithm. The user can also choose whether the text should be encoded using an assembler DLL or written in a high-level language, in this case C ++.

### Encrypt
<img src="/1.png" >

### Decrypt
<img src="/2.png" >

In the case of multithreading, the user has the possibility to enter his own number of threads, however, any exceeding of the limit is signaled so that the user is not able to call the program for incorrect parameters. There is also an option to automatically recognize the number of threads.


The appearance of the result files for individual operations.
<img src="/3.png" >

