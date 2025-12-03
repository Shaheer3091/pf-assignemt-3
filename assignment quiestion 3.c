#include <stdio.h>
#include <string.h>
 

struct employ{
    int id;
    char name[20];
    int salary;
    int number;
    char email[30];
    char designation[70];
};
 

int salary(int a){
    int z = 0;

    if(a==1) z=20000;
    else if(a==2) z=30000;
    else if(a==3) z=50000;
    else if(a==4) z=80000;
    else if(a==5) z=100000; 
    return z;
}

void displayemp(struct employ e[],int n);
void displayemp(struct employ e[],int n){
	if(n>0){
	int id,i;
    printf("Enter the id you want to search\n");
    scanf("%d",&id);
    for(i=0;i<n;i++){
    if(e[i].id==id){
        printf("\nRecord found");
        printf("\nNAME:%s\n",e[i].name);
        printf("ID:%d\n",e[i].id);
        printf("Email:%s\n",e[i].email);
        printf("Contact:%d\n",e[i].number);
        printf("Designation:%s\n",e[i].designation);
        printf("Salary:%d\n\n",e[i].salary);
		break;}   
		else{("\nNO RESULT FOUND");}
		
		}
		}
  
 else{printf("Input some data first\n");} 
}
    

int main(){
    int desig,id,exp,cased=0,n=0,i;
    char name[20],department[20],designation[70];
    struct employ e[n];
while(cased!=5){    
    printf("This is Employee data software\n\n");
    printf("1.Add new employee data\n");
    printf("2.Search employee with Id\n");
    printf("3.Search employee wth name\n");
    printf("4.Search employee with designation\n");
    printf("5.Exit\n");
    scanf("%d",&cased);
    switch(cased){
case 1:
	
{	printf("Enter the number of emplo0yee you want to add\n");
	scanf("%d",&n);
	
    for(i=0;i<n;i++){

    printf("Enter ID %d: ",i+1);
    scanf("%d", &e[i].id);

    printf("Enter name: ");
    scanf("%s", e[i].name);

    printf("Enter email: ");
    scanf("%s", e[i].email);

    printf("Enter number: ");
    scanf("%d", &e[i].number);

     do{
    printf("Enter designation\n1.Intern\n2.Junior\n3.Senior\n4.Manager\n5.Director\n");
    scanf("%d", &desig);

    switch(desig){
        case 1: strcpy(e[i].designation,"Intern"); break;
        case 2: strcpy(e[i].designation,"Junior"); break;
        case 3: strcpy(e[i].designation,"Senior"); break;
        case 4: strcpy(e[i].designation,"Manager"); break;
        case 5: strcpy(e[i].designation,"Director"); break;
    }} 
	while(desig<1||desig>5) ;

    e[i].salary = salary(desig);
    printf("Salary = %d\n", e[i].salary);
}
break;  }  

 

 case 02:displayemp(e,n);
 break;

   case 03:
   
   
   { printf("Enter the name you want to search\n");
    scanf("%s",name);
    
    for(i=0;i<n;i++){
    if(stricmp(e[i].name,name)==0){
        printf("\nRecord found");
        printf("\nNAME:%s\n",e[i].name);
        printf("ID:%d\n",e[i].id);
        printf("Email:%s\n",e[i].email);
        printf("Contact:%d\n",e[i].number);
        printf("Designation:%s\n",e[i].designation);
        printf("Salary:%d\n\n",e[i].salary); }   else{("\nNO RESULT FOUND");}}break;}
        
 case 04:{printf("Enter the designation you want to search  (only first letter uppercase)\n");
    scanf("%s",&designation);

    for(i=0;i<n;i++){
    if(stricmp(e[i].designation,designation)==0){
        printf("\nRecord found");
        printf("\nNAME:%s\n",e[i].name);
        printf("ID:%d\n",e[i].id);
        printf("Email:%s\n",e[i].email);
        printf("Contact:%d\n",e[i].number);
        printf("Designation:%s\n",e[i].designation);
        printf("Salary:%d\n",e[i].salary);}
        else{("\nNO RESULT FOUND");}
     
 }break;}
 
 case 05:printf("Exiting program........");break;}
        
 
    
}
}



