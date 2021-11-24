#include "./inc/bill_operations.h"

/* Start of Application */
int main(){
	int option;
	time_t date;
	time(&date);
	orders order,order_to_show;
	char saveBill = 'y',contFlag='y';
	FILE *fp;
	char name[50];

	/* Dashboard */
	while(contFlag =='y'){
		system("clear");
		float total=0;
		int invoiceFound = 0;
	printf("\t====== GENERAL STORE========");
	printf("\n\nPlease select an operation :");
	printf("\n\n1. Generate Invoice");
	printf("\n\n2. Show all Invoices");
	printf("\n\n3. Search Invoice");
	printf("\n\n4. Exit");

	printf("\n\nYour choice:\t");
	scanf("%d",&option);
	fgetc(stdin);
	
	switch(option){
		case 1:
		system("clear");
		printf("Enter the name of customer :\t");
		fgets(order.customer,50,stdin);
		order.customer[strlen(order.customer)-1] =0;
		//strcpy(ord.date,_DATE_);
		printf("\n Enter number of items buyed:\t");
		scanf("%d",&order.numOfitems);

		for(int i=0;i<order.numOfitems;i++){
			fgetc(stdin);
			printf("\n\n");
			printf("Please Enter the name of item %d:\t",i+1);
			fgets(order.itm[i].item,20,stdin);
			order.itm[i].item[strlen(order.itm[i].item)-1] = 0;
			printf("Please Enter the Quantity:\t\t");
			scanf("%f",&order.itm[i].qty);
			printf("Please enter the unit price:\t\t");
			scanf("%f",&order.itm[i].price);
			total+= total_bill(order.itm[i].qty, order.itm[i].price);

			
		}
		generate_bill_header(order.customer,date);
		for(int i=0;i<order.numOfitems;i++){
			generate_bill_body(order.itm[i]);
		}
		generate_bill_footer(total);
		printf("\n Do you want to save invoice [y/n]:\t");
		scanf("%s",&saveBill);

		if(saveBill == 'y'){
			fp = fopen("BillInvoice.txt","a+");
			fwrite(&order,sizeof(orders),1,fp);			
			if(fwrite != 0)
			printf("\n Invoice Successfully Saved\n");
			else
			printf("\n Error in  Saving\n");
			fclose(fp);

		}
		break;

		case 2:
		system("clear");
		fp = fopen("BillInvoice.txt","r");
		if(fp){

		
		printf("\n ****** Your Previous Invoices ********\n");
		while (fread(&order_to_show,sizeof(orders),1,fp))
		{
			float total_to_show = 0;
			generate_bill_header(order_to_show.customer, date);
			for(int i = 0; i<order_to_show.numOfitems;i++){
				generate_bill_body(order_to_show.itm[i]);
				total_to_show+= order_to_show.itm[i].qty * order_to_show.itm[i].price;
			}
			generate_bill_footer(total_to_show);	
		
		}		fclose(fp);
		}
		else{
			printf("\n************* Sorry no Saved Invoices**************\n");
		}
		break;

		case 3:
		system("clear");
		printf("\n Enter name of customer:\t");
		fgets(name,50,stdin);
		name[strlen(name)-1]=0;
		fp = fopen("BillInvoice.txt","r");
		printf("\n \t****** Invoice of %s ********",name);
		while (fread(&order_to_show,sizeof(orders),1,fp))
		{
			
			float total_to_show = 0;
			if(!strcmp(order_to_show.customer,name)){
				generate_bill_header(order_to_show.customer, date);
				for(int i = 0; i<order_to_show.numOfitems;i++){
				generate_bill_body(order_to_show.itm[i]);
				total_to_show+= order_to_show.itm[i].qty * order_to_show.itm[i].price;
			}
			generate_bill_footer(total_to_show);	
			invoiceFound = 1;
		
		}	
			}
			if(!invoiceFound){
				printf("\nSorry the invoice for %s does not exist",name);
			}
			fclose(fp);
		break;

		case 4:
		printf("\n\t\t Bye bye \n\n");
		exit(0);
		break;
		default:
		printf("Sorry invalid Option");
		break;
		
	}
	printf("\n Do you want to perform another operation [y/n]\t");
	scanf("%s",&contFlag);
	}
	printf("\n\t\t Bye bye \n\n");
	return 0;
}
