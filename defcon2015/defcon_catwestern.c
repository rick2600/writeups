//gcc -o defcon_catwestern defcon_catwestern.c -masm=intel -z execstack

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


unsigned long long regs[16];

char *code_start, *code_back;

char result[4096];

void parse_init_state(char *init_state)
{
  char *a, *b = init_state, buf[45];
  int i = 0;  

  while(1)
  {
    memset(buf, 0, sizeof(buf));
    a = strchr(b, '=');
    if (!a)
      break;
    a += 1;
    strncpy(buf, a, strchr(a, '\n')-a);
    
    regs[i] = strtoull(buf, NULL, 16);

    i++;

    b = a;
  }

}

void exec_code(void)
{
   asm("mov rax, [0x6020c0]\n");
   asm("mov rbx, [0x6020c8]\n");
   asm("mov rcx, [0x6020d0]\n");
   asm("mov rdx, [0x6020d8]\n");
   asm("mov rsi, [0x6020e0]\n");
   asm("mov rdi, [0x6020e8]\n");
   asm("mov r8,  [0x6020f0]\n");
   asm("mov r9,  [0x6020f8]\n");
   asm("mov r10, [0x602100]\n");
   asm("mov r11, [0x602108]\n");
   asm("mov r12, [0x602110]\n");
   asm("mov r13, [0x602118]\n");
   asm("mov r14, [0x602120]\n");
   asm("mov r15, [0x602128]\n");

   asm("jmp [0x602140]\n");

   asm("mov [0x6020c0], rax\n");
   asm("mov [0x6020c8], rbx\n");
   asm("mov [0x6020d0], rcx\n");
   asm("mov [0x6020d8], rdx\n");
   asm("mov [0x6020e0], rsi\n");
   asm("mov [0x6020e8], rdi\n");
   asm("mov [0x6020f0], r8\n");
   asm("mov [0x6020f8], r9\n");
   asm("mov [0x602100], r10\n");
   asm("mov [0x602108], r11\n");
   asm("mov [0x602110], r12\n");
   asm("mov [0x602118], r13\n");
   asm("mov [0x602120], r14\n");
   asm("mov [0x602128], r15\n");


    sprintf(result, 
      "rax=0x%llx\n"
      "rbx=0x%llx\n"
      "rcx=0x%llx\n"
      "rdx=0x%llx\n"
      "rsi=0x%llx\n"
      "rdi=0x%llx\n"
      "r8=0x%llx\n"
      "r9=0x%llx\n"
      "r10=0x%llx\n"
      "r11=0x%llx\n"
      "r12=0x%llx\n"
      "r13=0x%llx\n"
      "r14=0x%llx\n"
      "r15=0x%llx\n",
      regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7], 
      regs[8], regs[9], regs[10], regs[11], regs[12], regs[13], regs[14], regs[15]
    );


}


int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;   

  char init_state[4097], code[4096];

  portno = 9999;

  /* Create a socket point */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    perror("ERROR opening socket");
    exit(1);
  }
  //server = gethostbyname(argv[1]);
  server = gethostbyname("catwestern_631d7907670909fc4df2defc13f2057c.quals.shallweplayaga.me");

  if (server == NULL)
  {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  /* Now connect to the server */
  if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("ERROR connecting");
    exit(1);
  }


  /* Now read server response */
  bzero(init_state, 4096);
  n = read(sockfd, init_state, 4096);     
  if (n < 0)
  {
  perror("ERROR reading from socket");
  exit(1);
  }

  bzero(code, 4096);
  n = read(sockfd, code, 4096);
  if (n < 0)
  {
    perror("ERROR reading from socket");
    exit(1);
  }

  code_start = strchr(code, ':') + 3;
  code_back = (char *)0x400b23;

  parse_init_state(init_state + strlen("****Initial Register State****") + 1);
  memcpy(code_start+n-68+1, "\xFF\x24\x25\x60\x31\x60\x00", 7);
  exec_code();
  write(sockfd, result, strlen(result));

  bzero(result, 4096);
  n = read(sockfd, result, 4096);
  if (n < 0)
  {
    perror("ERROR reading from socket");
    exit(1);
  }
  printf("%s\n", result);



  return 0;
}
