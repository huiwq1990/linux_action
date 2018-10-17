int main(int argc, char *argv[]) 
{
int fd;
printf("argc = %d ",argc);
fd = *argv[1];
printf("fd = %d",fd);
char *s = "zzzzzzzzzzzzzzzzzzz";
write(fd, (void *)s, strlen(s));
close(fd);
return 0;
}