#include "shell.hh"
#include <iostream>
#include <string>
#include <sys/wait.h>
//#include <uistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{ std::string input;

  // ToDo: Vervang onderstaande regel: Laad prompt uit bestand
  std::string prompt = "ToDo: Laad de prompt uit een bestand! ";

  while(true)
  { std::cout << prompt;                   // Print het prompt
    std::getline(std::cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "seek") seek();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (std::cin.eof()) return 0; } }      // EOF is een exit

void new_file() // ToDo: Implementeer volgens specificatie.
{ std::cout << "ToDo: Implementeer hier new_file()" << std::endl;
  std::string filename;
  std::string filetext;
  std::cout << "voer bestandnaam in"<< std::endl;
  std::getline(std::cin, filename);
  std:: cout << "geef invoer" << std::endl;
  std::getline(std::cin, filetext);
  int fd = creat(filename.c_str(), 0777);
  ssize_t a = write(fd, filetext.c_str(), filetext.size());
  
  }

void list() // ToDo: Implementeer volgens specificatie.
{ 
  if(fork()== 0){
      char *arguments[] = {(char*)"/bin/ls", (char*)"-la", (char*)0};
      execv("/bin/ls", arguments);
  }
  else{
      int eindstatus;
      wait(&eindstatus);
  }


 }

void find() // ToDo: Implementeer volgens specificatie.
{ std::cout << "wat zoek je" << std::endl;
  std::string zoeken;
  std::getline(std::cin, zoeken);
  int pipezoek[2];
  int status;
  int controle = pipe(pipezoek);
  if((controle) == -1){
      perror("pipetime no");
      exit(1);
  }
  int id = fork();
  if(id == 0){
      char *arguments[] = {(char*)"find", (char*)"./",(char*)0};
      close(pipezoek[0]);
      dup2(pipezoek[1], STDOUT_FILENO);
      execv("/usr/bin/find",arguments);
  }
  id = fork();
  if(id == 0){
      char *parameter[]= {(char*)"grep", (char*)zoeken.c_str(), (char*)0};
      close(pipezoek[1]);
      dup2(pipezoek[0], STDIN_FILENO);
      execv("/usr/bin/grep",parameter);
  }
  close (pipezoek[0]);
  close(pipezoek[1]);
  waitpid(-1, &status, 0);
  waitpid(-1, &status, 0);
   }

void seek() // ToDo: Implementeer volgens specificatie.
{ std::cout << "ToDo: Implementeer hier seek()" << std::endl;
  std::string loop = "loop.txt";
  int seek_make = creat("seek.txt", 0777);
  int loop_make = creat(loop.c_str(), 0777);
  write(loop_make, "x", 1);
  std::string message = "\0";
  for(int i = 0; i < 50000; i++){

write(loop_make, "\0", 1);

}
write(loop_make, "x", 1);
write(seek_make, "x", 1);
lseek(seek_make, 50000, SEEK_END);
write(seek_make, "x", 1);

 if(fork()== 0){
      char *arguments[] = {(char*)"/bin/ls", (char*)"-la", (char*)0};
      execv("/bin/ls", arguments);
  }
  else{
      int eindstatus;
      wait(&eindstatus);
  }

}

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.

