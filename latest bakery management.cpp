#include<iostream>
#include<cctype>
#include<iomanip>
#include<string>
#include<windows.h>
#include<fstream>
#include<dos.h>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	//color text - global use

struct staffDetail
{
	string name;
	int Id;
	string position;
	string dayWork;
	string hourWork;
	
};
staffDetail staff[8];

void cafeDetail();

void userCustomer(int &,int &,float &,float &,float &,float &,float &, float &, float [], ofstream &);
void userStaff(int ,int ,int [][2],float ,float, float,float,float,int, float[],string, string, float, float, float, ifstream &);

void cafeMenu(int );
float calcBills(int, int );
float calcDiscount(float);
void calcQuantity(char, int &, int &, int &, int &, int);
float averageSale(float);
void calcFeedback(int, int &, int &, int &, int &);
void displayBill(float, float,float, float, float, float, int [], ofstream &);
void calcItemSale(int, float, float &, float &, float &, float &);
void calcItem(int, float, float &, float &, float &, float &);
void printAllSale(float, float, float, float, float,int, float[], float, float, float, string, string);

void employeeDetails(int);
void calcMinMax(float [], float&, float&, string &, string &);
void sortSale(float []);

void loadingBar();
void welcomeMessage();
void closeMessage();


int main()
{
	char nextUser = 'Y';
	int user,menu,feedback, h=0, s=0,buy,customer=0;
	float totalPrice,totalCake=0,totalPie=0,totalBread=0,totalDrink=0, totalAll=0,newPrice=0,price=0;
	float avg;
	float arrPrice[4]={0};
	
	int arrFeedback[100][2] = {0};
	int sumH, sumS;
	
	float max=0.00, min=999.00;
	string maxName, minName;
	
	string password = "2017";
	string pass;
	char nextStaff;
	char promotion;
	
	ifstream inFile;
	ofstream outdata;
		
	SetConsoleTextAttribute(console,240);
	cout << setiosflags(ios::fixed) << setprecision(2);
	
	SetConsoleTextAttribute(console,240);
	cout << " ";
	system("cls");

		cafeDetail();
		
		//Display to user option (customer or staff)
		while(toupper(nextUser)!='N')
	{
		system("cls");
		SetConsoleTextAttribute(console,244);
		cout << "Do you want enter as Customer or Staff? \n\n";
		SetConsoleTextAttribute(console,240);
		cout << "1)Customer \n\n";
		cout << "2)Staff \n\n";
		cout << "Please enter number 1 or 2 : ";
		cin >> user;
		cout << endl;
		
		system("cls");
		
		if(user==1)
		{
			welcomeMessage();
			
			SetConsoleTextAttribute(console,240);
			cout << "\n\n\n\nDo you want to look at the available promotion before purchase items?  " <<endl;
			cout << "[Y:YES , N:NO] : " ;
			cin >> promotion;
			system("cls");
			
			if(toupper(promotion)=='Y')
			{
				MessageBox(0,"Hello and welcome to the bakery!","Promotion",MB_OK);
				MessageBox(0,"There are 2 promotion available.","Promotion",MB_OK);
				MessageBox(0,"1)Purchase more than RM50 and get 10% discount.","Promotion",MB_OK);
				MessageBox(0,"2)Purchase more than RM100 and get 20% discount.","Promotion",MB_OK);
				MessageBox(0,"Don't wait anymore and get your promotion now! Thank You :D","Promotion",MB_OK);
			}
			
			userCustomer(buy,menu,price,newPrice,totalCake,totalPie,totalBread,totalDrink, arrPrice,outdata);
			
				cout<<"\nFEEDBACK CUSTOMERS : ";
				cout<<"\nDo you like our services?\nEnter 1-Good Service / 2-Bad Service : ";
				cin>>feedback;
				calcFeedback(feedback,h,s,sumH,sumS); //ask customer for feedback before end the program
			
			totalAll += newPrice; // sum all price for ALL CUSTOMER
			avg = averageSale(totalAll);
		
			for(int r=customer; r<customer+1; r++)
			{
				for(int c=0; c<1; c++)
			{
				arrFeedback[r][0] = sumH;
				arrFeedback[r][1] = sumS;
			}
			}
			
			customer++;
		}
		
		else if(user==2)
		{

			cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tPlease Enter Staff Password : ";
			cin >> pass;
			system("cls");
			
			if(pass==password)
			{
				nextStaff = 'N';
				while(toupper(nextStaff)!='Y')
			{
				calcMinMax(arrPrice,min,max,maxName,minName);
				userStaff(h,s,arrFeedback,totalCake,totalPie,totalBread,totalDrink,totalAll,customer, arrPrice,maxName, minName, max, min, avg, inFile);
			
				cout << "\nDo you want to return to main menu? [Y:YES , N:NO] : ";
				cin >> nextStaff;
			}
			}
			
			else
			{

				SetConsoleTextAttribute(console,270);
				cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid password!" << endl;
				SetConsoleTextAttribute(console,240);
			}
		}
		
		cout<< "\nNext User ? [Y:YES N:NO] : " ;
		cin >> nextUser;
	}
	
	system("cls");
	cin.get();
	closeMessage();
}

void cafeDetail()
{
	//Bakery's details
	SetConsoleTextAttribute(console,240);
	cout << "\n\n\n\n" ;
	cout << "\t\t\t\t\t    WELCOME TO BAKERY \n";
	cout << "\t\t\t\t\t    BAKERY'S DETAILS \n" ;
	SetConsoleTextAttribute(console,241);
	cout << "\t\t\t________________________________________________________\n";
	cout << "\t\t\t|                                                       |"<< endl;
	cout << "\t\t\t|   Operating hours : 9:00 A.M ~ 10:00 P.M              |" << endl;
	cout << "\t\t\t|_______________________________________________________|" << endl;
	SetConsoleTextAttribute(console,242);
	cout << "\t\t\t|                                                       |"<< endl;
	cout << "\t\t\t|   Operating days : Monday ~ Saturday                  |" << endl;
	cout << "\t\t\t|_______________________________________________________|" << endl;
	SetConsoleTextAttribute(console,243);
	cout << "\t\t\t|                                                       |"<< endl;
	cout << "\t\t\t|  Terms and Condition :                                |" << endl;
	cout << "\t\t\t|  1)Purchased item cannot be return back.              |" << endl;
	cout << "\t\t\t|  2)Receipt are provided as purchase prove.            |" << endl;
	cout << "\t\t\t|  3)Cancelling order not allowed.                      |" << endl;
	cout << "\t\t\t|  3)Only cash and credit card allow to make payment    |" << endl;
	cout << "\t\t\t|_______________________________________________________|" << endl;
	SetConsoleTextAttribute(console,244);
	cout << "\t\t\t|                                                       |"<< endl;
	cout << "\t\t\t|  Any problem refer to :                               |" << endl;
	cout << "\t\t\t|  1)Encik.Yadiy Nurhakim (Manager 1)                   |" << endl;
	cout << "\t\t\t|  2)Encik.Muhhamad Arif (Manager 2)                    |" << endl;
	cout << "\t\t\t|_______________________________________________________|" << endl;
	SetConsoleTextAttribute(console,240);
	
	cin.get();
	system("cls");
}

void userCustomer(int &buy,int &menu,float &price,float &newPrice,float &totalCake,float &totalPie,float &totalBread, float &totalDrink, float arrPrice[4], ofstream &outdata)
{
	int choice, quantity;
	float totalPrice=0;
	char diffBuy = 'Y';
	float totalCake1=0,totalPie2=0,totalBread3=0,totalDrink4=0;
	int quantityC=0, quantityP=0, quantityB=0, quantityD=0;
	
	int arrQuantity[4];
	
	outdata.open("printBill.txt");
				
	while(tolower(diffBuy)!='n')
	{
		char nextBuy='Y';
		
		//Customer menu
		system("cls");
		SetConsoleTextAttribute(console,243);
		cout << "			BAKERY'S MENU \n";
		cout << "			*************\n";
		SetConsoleTextAttribute(console,240);
		cout << "1) CAKE \n\n";
		cout << "2) PIE \n\n";
		cout << "3) BREAD \n\n";
		cout << "4) DRINKS \n\n";
		cout << "Please enter number 1,2,3 or 4 from the list of bakery's menu. : ";
		cin >> menu;
		
		system("cls");
		cin.get();
		
		while(toupper(nextBuy)!='N')
		{
			system("cls");
			cafeMenu(menu);
			
			cout << "\nEnter the menu you wish to buy : " ;
			cin >> buy;
			
			if(buy>=1 && buy<=6){
			cout << "\nEnter the quantity : ";
			cin >> quantity;
			
			calcQuantity(menu,quantityC, quantityP, quantityB, quantityD,quantity);
			
			price = calcBills(menu,quantity);
						
			totalPrice += price; //sum all price for A CUSTOMER
			
			calcItemSale(menu,price,totalCake,totalPie,totalBread,totalDrink); //sale each item for A CUSTOMER
			calcItemSale(menu,price,totalCake1,totalPie2,totalBread3,totalDrink4);
			
			//array price
			arrPrice[0] = totalCake;
			arrPrice[1] = totalPie;
			arrPrice[2] = totalBread;
			arrPrice[3] = totalDrink;
			
		}
		
		else
			cout << "\nINVALID INPUT!" << endl << endl;
			system("cls");			
			cout << "\nY)YES N)NO" << endl;
			cout << "Do you want to continue buy same type of menu ? : ";	// same category (looping) if not inner loop : false
			cin >> nextBuy; 

		}
		cout << "\nY)YES N)NO" << endl;
		cout << "Do you wish to continue buy another type of menu? : "; // buy more (looping) if not : false
		cin >> diffBuy;
	}
	newPrice = calcDiscount(totalPrice);
	
	//array quantity
	arrQuantity[0] = quantityC;
	arrQuantity[1] = quantityP;
	arrQuantity[2] = quantityB;
	arrQuantity[3] = quantityD;
	
	displayBill(totalPrice,newPrice,totalCake1,totalPie2,totalBread3,totalDrink4, arrQuantity, outdata); //print to customer the bill
	
	outdata.close();
}

void userStaff(int h,int s,int arrFeedback[][2],float totalCake,float totalPie, float totalBread,float totalDrink,float totalAll,int customer, float arrPrice[],string maxName, string minName, float max, float min, float avg, ifstream &inFile)
{
	int staff;
	int n = 0;
	int saleTarget[4];
	char itemName[4][10];
	
	inFile.open("target.txt");
	
	SetConsoleTextAttribute(console,243);
	//Staff menu
	cin.get();
	system("cls");
	cout << "			STAFF'S MENU \n";
	cout << "			*************\n";
	SetConsoleTextAttribute(console,240);
	cout << "1) CUSTOMER'S FEEDBACK \n\n";
	cout << "2) SALES REPORT \n\n";
	cout << "3) STAFF DETAILS \n\n";
	cout << "4) SALES TARGET \n\n";
	cout << "Please enter number 1 or 2 from the list of staff's menu. : ";
	//User enter their choice
	cin >> staff;
					
	system("cls");
	cin.get();
					
	if(staff==1)
	{
		int n = 0;
		
		for(int r=0; r<customer; r++)
		{
			cout << "\nCustomer " << n+1 << ": " << endl;
			cout << "Happy : " << arrFeedback[r][0] << endl ;
			cout << "Sad   : " << arrFeedback[r][1] << endl;
			
			n++;
		}
		
		cout << "\nTotal Feedback With Happy Respond From All Customer Is : " << h << endl;
		cout << "\nTotal Feedback With Sad Respond From All Customer Is : " << s << endl;
	}
	else if(staff==2)
	{
		printAllSale(totalCake,totalPie,totalBread,totalDrink,totalAll,customer,arrPrice,max,min,avg,maxName,minName);
	}
	else if(staff==3)
	{
		int searchId;
		
		cout<<"\nEnter staff ID : ";
		cin>>searchId;
		employeeDetails( searchId);
	}
	else if(staff==4)
	{
		for(int i=0; i<10; i++)
		{
			inFile >> itemName[i];
			inFile >> saleTarget[i];
		}
		
		SetConsoleTextAttribute(console,241);
		cout << "\n   SALES TARGET FOR MAIN CATEGORY   " << endl;
		cout << "************************************" << endl << endl;
		cout << itemName[0] << "  : " << saleTarget[0] << endl << endl;
		cout << itemName[1] << "   : " << saleTarget[1] << endl << endl;
		cout << itemName[2] << " : " << saleTarget[2] << endl << endl;
		cout << itemName[3] << " : " << saleTarget[3] << endl << endl << endl;
		SetConsoleTextAttribute(console,240);
	}
	else
		cout << "\nInvalid user code !" << endl;
		
	inFile.close();
}

void cafeMenu(int menu)
{
	//cafe menu
	if(menu==1)
	{
		SetConsoleTextAttribute(console,241);
		cout << "===========================================================\n";
		cout << "List of Cakes 				Price 					\n";
		cout << "===========================================================\n";
		cout << "1) Red Velvet				Slice:RM6.00 			\n";
		cout << "-----------------------------------------------------------\n";			 
		cout << "2) Chocolate Cake 			Slice:RM6.00 			\n";
		cout << "-----------------------------------------------------------\n";
		cout << "3) Blueberry Cake			Slice:RM6.00 			\n";
		cout << "-----------------------------------------------------------\n";
		cout << "4) Oreo Cake				Slice:RM6.00 			\n";
		cout << "-----------------------------------------------------------\n";
		cout << "5) Mango Cake				Slice:RM6.00 			\n";
		cout << "-----------------------------------------------------------\n";
		cout << "6) Cheese Cake				Slice:RM6.00 			\n";
		cout << "===========================================================\n";
		SetConsoleTextAttribute(console,240);
	}

	else if(menu==2)
	{
		SetConsoleTextAttribute(console,241);
		cout << "==========================================================\n";
		cout << "List of Pies 				Price 					\n";
		cout << "==========================================================\n";
		cout << "1) Apple Pie				Slice:RM3.00 			\n";
		cout << "----------------------------------------------------------\n";
		cout << "2) Chocolate Pie			Slice:RM3.00 			\n";
		cout << "----------------------------------------------------------\n";
		cout << "3) Blueberry Pie			Slice:RM3.00 			\n";
		cout << "----------------------------------------------------------\n";
		cout << "4) Pineaple Pie				Slice:RM3.00 		    \n";
		cout << "----------------------------------------------------------\n";		 
		cout << "5) Honey Pie				Slice:RM3.00 			\n";
		cout << "----------------------------------------------------------\n";		 
		cout << "6) Lychee Pie				Slice:RM3.00 			\n";
		cout << "==========================================================\n";
		SetConsoleTextAttribute(console,240);
	}		 

	else if(menu==3)
	{
		SetConsoleTextAttribute(console,241);
		cout << "=================================================\n";
		cout << "List of Breads 			Price 					\n";
		cout << "=================================================\n";
		cout << "1) Pizza Bread			RM3.00				\n";
		cout << "-------------------------------------------------\n";		 
		cout << "2) Sausage Bread		RM3.00				\n";
		cout << "-------------------------------------------------\n";		 
		cout << "3) Garlic Bread			RM3.00				 \n";
		cout << "-------------------------------------------------\n";		 
		cout << "4) Mexico Bread			RM3.00				\n";
		cout << "-------------------------------------------------\n";		 
		cout << "5) Cheese Bread 		RM3.00				 \n";
		cout << "-------------------------------------------------\n";		 
		cout << "6) Chicken Floss Bread		RM3.00				\n";
		cout << "=================================================\n";
		SetConsoleTextAttribute(console,240);
	}

	else if(menu==4)
	{
		SetConsoleTextAttribute(console,241);
		cout << "==================================================\n";
		cout << "List of Drinks 				Price 				\n";
		cout << "==================================================\n";
		cout << "1) Ice Lemon Tea			RM2.00 				\n";
		cout << "--------------------------------------------------\n";		 
		cout << "2) Blackcurrent Juice			RM2.00 				\n";
		cout << "--------------------------------------------------\n";		 
		cout << "3) Mango Juice				RM2.00 				\n";
		cout << "--------------------------------------------------\n";		 
		cout << "4) Chocolate				RM2.00 				\n";
		cout << "--------------------------------------------------\n";		 
		cout << "5) Latte				RM2.00 				\n";
		cout << "--------------------------------------------------\n";		 
		cout << "6) Coffee				RM2.00 				\n";
		cout << "==================================================\n";
		SetConsoleTextAttribute(console,240);
	}
	else
		cout << "Invalid menu code!" << endl;
}

float calcBills(int menu, int quantity)
{
	float price;
	
	if (menu==1)
	{
		price=6.00*quantity;
	}
	else if (menu==2)
	{
		price=3.00*quantity;
	}
		
	else if (menu==3)
	{
		price=3.00*quantity;
	}
	else if (menu==4)
	{
		price=2.00*quantity;
	}
	else
	cout << "invalid menu!" << endl;
	
	return price;		
}

float calcDiscount(float totalPrice)
{
	float discount, newPrice;
	
	if(totalPrice<50)
		discount=0;
		
	else if(totalPrice>=50.00 && totalPrice<100.00)
		discount=0.1*totalPrice;
		
	else if(totalPrice>=100.00)
		discount=0.2*totalPrice;
		
	//calculate price after discount
	newPrice=totalPrice-discount;
	
	return newPrice;
}

void calcQuantity(char menu, int &quantityC, int &quantityP, int & quantityB, int & quantityD, int quantity)
{
	if(menu==1)
		quantityC += quantity;
	else if(menu==2)
		quantityP+= quantity;
	else if(menu==3)
		quantityB+= quantity;
	else if(menu==4)
		quantityD+= quantity;
}

float averageSale(float totalAll)
{
	float avg;
	
	avg = totalAll/4;
	
	return avg;
}

void calcFeedback(int feedback, int &h, int &s, int &sumH, int &sumS)
{		
		//to calculateall sum for each feedback (happy and sad)
		if(feedback==1)
			h++;
		else if(feedback==2)
			s++;
			
		// to calculate feedback for each customer
		sumH = 0;
		sumS = 0;
		if(feedback==1)
			sumH ++;
		else if(feedback==2)
			sumS ++;
}

void displayBill(float totalPrice, float newPrice,float totalCake1 , float totalPie2 , float totalBread3 , float totalDrink4 , int arrQuantity[4], ofstream &outdata)
{
	system("cls");
	//bill for customer at console
	cout << endl;
	SetConsoleTextAttribute(console,243);
	cout << "............................................................" << endl; 
	SetConsoleTextAttribute(console,244);
	cout << "                  BAKERY'S RECEIPT" << endl;
	SetConsoleTextAttribute(console,243);
	cout << "............................................................" << endl;
	SetConsoleTextAttribute(console,244);
	cout << "Total Purchased Menu :                                      " << endl;  
	cout << endl;
	SetConsoleTextAttribute(console,240);
	cout << "Cake           : RM" << totalCake1 << endl;
	cout << "Quantity Cake  : " << arrQuantity[0] << endl << endl;
	cout << "Pie            : RM" << totalPie2 << endl;
	cout << "Quantity Pie   : " << arrQuantity[1] << endl << endl;
	cout << "Bread          : RM" << totalBread3 << endl;
	cout << "Quantity Bread : " << arrQuantity[2] << endl << endl;
	cout << "Drink          : RM" << totalDrink4 << endl;
	cout << "Quantity Drink : " << arrQuantity[3] << endl <<endl;
	SetConsoleTextAttribute(console,243);
	cout << "............................................................" << endl;
	SetConsoleTextAttribute(console,240);  
	cout << "Total Price (Before Discount) : RM" << totalPrice << endl << endl;
	cout << "Total Price (Ater Discount)   : RM" << newPrice << endl;
	SetConsoleTextAttribute(console,243);
	cout << "............................................................" << endl; 
	SetConsoleTextAttribute(console,240);
	cout << " *Make sure you receive a receipt*" << endl << endl;
	cout << " *Any purchased menu cannot be return*" << endl;
	SetConsoleTextAttribute(console,243);
	cout << "............................................................" << endl; 
	SetConsoleTextAttribute(console,244);
	cout << "            ~Thank You, Please Come Again~" << endl;         
	SetConsoleTextAttribute(console,243);
	cout << "............................................................" << endl;
	cout << "............................................................" << endl << endl;
	system("pause");
	SetConsoleTextAttribute(console,240);
	system("cls");

	loadingBar();
	
	//print bill at notepad
	outdata << endl;
	outdata << "............................................................" << endl; 
	outdata << "                  BAKERY'S RECEIPT" << endl;
	outdata << "............................................................" << endl;
	outdata << "Total Purchased Menu :                                      " << endl;  
	outdata << endl;
	outdata << "Cake           : RM" << totalCake1 << endl;
	outdata << "Quantity Cake  : " << arrQuantity[0] << endl << endl;
	outdata << "Pie            : RM" << totalPie2 << endl;
	outdata << "Quantity Pie   : " << arrQuantity[1] << endl << endl;
	outdata << "Bread          : RM" << totalBread3 << endl;
	outdata << "Quantity Bread : " << arrQuantity[2] << endl << endl;
	outdata << "Drink          : RM" << totalDrink4 << endl;
	outdata << "Quantity Drink : " << arrQuantity[3] << endl <<endl;
	outdata << "............................................................" << endl;
	outdata << "Total Price (Before Discount) : RM" << totalPrice << endl << endl;
	outdata << "Total Price (Ater Discount)   : RM" << newPrice << endl;
	outdata << "............................................................" << endl; 
	outdata << " *Make sure you receive a receipt*" << endl << endl;
	outdata << " *Any purchased menu cannot be return*" << endl;
	outdata << "............................................................" << endl; 
	outdata << "            ~Thank You, Please Come Again~" << endl;         
	outdata << "............................................................" << endl;
	outdata << "............................................................" << endl << endl;
}

void calcItemSale(int menu, float price, float &totalCake, float &totalPie, float &totalBread, float &totalDrink)
{
	if(menu==1)
		totalCake += price;
		
	else if(menu==2)
		totalPie += price;
		
	else if(menu==3)
		totalBread += price;
	
	else if(menu==4)
		totalDrink += price;
}

void calcItem(int menu, float price, float &totalCake1, float &totalPie2, float &totalBread3, float &totalDrink4)
{
	if(menu==1)
		totalCake1 += price;
		
	else if(menu==2)
		totalPie2 += price;
		
	else if(menu==3)
		totalBread3 += price;
	
	else if(menu==4)
		totalDrink4 += price;
}

void calcMinMax(float totalSaleItem[], float& min, float& max, string &maxName, string &minName)
{
	string itemName[4] = {"Cake","Pie","Bread","Drink"};
	
	// to find the max and min of sales
	// to find the max and min item's name
	for(int i=0; i<4; i++)
	{
	if(totalSaleItem[i]>max)
	{
		max=totalSaleItem[i];
		maxName = itemName[i];
	}
	else
		if(totalSaleItem[i]<min)
		{
			min=totalSaleItem[i];
			minName = itemName[i];
		}
	}
	
	
}

void printAllSale(float totalCake, float totalPie, float totalBread, float totalDrink, float totalAll,int customer, float arrPrice[], float max, float min, float avg, string maxName, string minName)
{
	//report for staff
	SetConsoleTextAttribute(console,244);
	cout << "             DAILY TOTAL SALE REPORT" << endl;
	cout << "*****************************************************" << endl;
	SetConsoleTextAttribute(console,245);
	cout << "    Total Sale (Cake)  : RM" << totalCake << endl;
	cout << "    Total Sale (Pie)   : RM" << totalPie << endl;
	cout << "    Total Sale (Bread) : RM" << totalBread  << endl;
	cout << "    Total Sale (Drink) : RM" << totalDrink  << endl << endl;
	cout << "    Total Sale Of Item in Descending Order : " << endl;
	sortSale(arrPrice);
	
	for(int i=0; i<4; i++)
	{
		cout << "    " << arrPrice[i] << "    " ;
	}
	
	cout << endl << endl;
	
	cout << "    Highest Sale is    : RM" << max << " (" << maxName << ")" << endl;
	cout << "    Lowest Sale is     : RM" << min << " (" << minName << ")" << endl << endl;
	
	cout << "    Total All Sale     : RM" << totalAll  << endl;
	cout << "    Average Of Sale    : RM" << avg << endl;
	
	cout << "    Total Customer     : " << customer << endl;
	SetConsoleTextAttribute(console,244);
	cout << "*****************************************************" << endl;
	SetConsoleTextAttribute(console,240);
}

void employeeDetails(int searchId)
{
	
	staffDetail staff[8]={
						{"Fireena Shaqueena",5111,"Cashier","Monday-Wednesday","9.00 a.m-3.00 p.m"},
						{"Hazim Aqasha",5112,"Cheff","Monday-Wednesday","9.00 a.m - 3.00 p.m"},
						{"Mazlin Razali",5113,"Cashier","Monday-Wednesday","3.00 p.m - 10.00 p.m"},
						{"Akmal Masrie",5114,"Cheff","Monday-Wednesday","3.00 p.m - 10.00 p.m"},
						{"Nur Fatihah",5115,"Cahsier","Thursday-Saturday","9.00 a.m - 3.00 p.m"},
						{"Ayumi Kito",5116,"Cheff","Thursday-Saturday","9.00 a.m - 3.00 p.m"},
						{"Farid Hasbullah",5117,"Cashier","Thursday- Saturday","3.00 p.m - 10 p.m"},
						{"Fais Haris",5118,"Cheff","Thursday- Saturday","3.00 p.m - 10 p.m"}
						};
						
	for(int i=0; i<8; i++)
	{	
		if(searchId==staff[i].Id)
		{
			cout<<"\n===============================================";
			cout<<"\n\t\tStaff's Detail";
			cout<<"\n===============================================";
			cout<<"\nName "<<"\t\t:\t"<<staff[i].name;
			cout<<"\n_______________________________________________";
			cout<<"\nStaff Id "<<"\t:\t"<<staff[i].Id;
			cout<<"\n_______________________________________________";
			cout<<"\nPosition as "<<"\t:\t"<<staff[i].position;
			cout<<"\n_______________________________________________";
			cout<<"\nDay Work "<<"\t:\t"<<staff[i].dayWork;
			cout<<"\n_______________________________________________";
			cout<<"\nHour Work "<<"\t:\t"<<staff[i].hourWork;
			cout<<"\n==============================================="<<endl;
		}			
	}			
						
}

void sortSale(float arrPrice[])
{
	int temp = 0;
	
	for(int i=1; i<4; i++)
	{
		for(int j=0; j<(4-j); j++)
		{
			if(arrPrice[j]<arrPrice[j+1])
			{
				temp = arrPrice[j];
				arrPrice[j] = arrPrice[j+1];
				arrPrice[j+1] = temp;
			}
		}
	}
}

void welcomeMessage()
{
	int len = 0, x, y=240; //240=white bg, black foreground
	
	cin.get();
	string text = "  HELLO AND WELCOME TO THE BAKERY! \n\t     ***************************************************************************** \n\n \t\t\t    YOU CAN ORDER YOUR MENU USING THIS PROGRAM...! \n\n \t\t\t    1)CHOOSE THE TYPE OF MENU YOU WANT ORDER \n\t\t\t    2)CHOOSE THE SPECIFIC MENU YOU WANT ORDER \n\t\t\t    3)DONT FORGET TO GET YOUR RECEIPT! \n\t\t\t    4)TAKE YOUR ORDER AT THE COUNTER AND ENJOY YOUR DAY! \n\n \t\t\t\t   ~Your Happiness Our Greatness~\n\n\t     ***************************************************************************** \n";
	len=text.length();
	cout << endl << endl << endl << endl << endl << endl << "\t\t\t\t";
	
	for (x=0; x<len;x++)
	{
		SetConsoleTextAttribute(console,y);
		cout << text[x];
		y++;
		if(y >245)
			y=240;
		Sleep(15); //pause between letters
	}
	
	cout << endl <<  endl << endl << endl;
	system("pause");
	system("cls");
}

void closeMessage()
{
	int len = 0, x, y=240; //240=white bg, black foreground
	
	cin.get();
	string text = "....................................................................\n\n\t\t\t\tTHANK YOU FOR USING OUR PROGRAM! \n\n\t\t\t\tCREDIT TO DEVELOPER BAKERY SYSTEM: \n\t\t\t\t1)NUR ADIBAH BINTI NORDIN \n\t\t\t\t2)NURHUSNA AASYIDA BINTI ZAINI \n\t\t\t\t3)NURUL HASANAH BINTI MD NOR AZMAN \n\n\t\t\t\t   WE GLAD TO HEAR YOUR COMMENT!  \n\t\t....................................................................\n";
	len=text.length();
	cout << endl << endl << endl << endl << endl << endl << "\t\t";
	
	for (x=0; x<len;x++)
	{
		SetConsoleTextAttribute(console,y);
		cout << text[x];
		y++;
		if(y >245)
			y=240;
		Sleep(30); //pause between letters
	}
	
	cout << endl <<  endl << endl << endl;
	system("pause");
	system("cls");
}

void loadingBar()
{
	
	SetConsoleTextAttribute(console,243);
 cout<<"\n\n\n\n\n\n\n\n\n\t\t\tPlease Wait : Printing the bill (Please check your bill )\n\n";
 
 SetConsoleTextAttribute(console,246);
 char a=177, b=219; //a=177 b=219
 cout<<"\t\t\t\t";
 for (int i=0;i<=40;i++)
 {
 	cout << a ;
 }
 cout<<"\r";
 cout<<"\t\t\t\t";
 for (int i=0;i<=40;i++)
 {
  cout<<b ;
  Sleep(70); //You can also use sleep function instead of for loop
 }
SetConsoleTextAttribute(console,240);
system("cls");
}

