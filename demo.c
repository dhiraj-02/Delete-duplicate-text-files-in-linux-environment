#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSIZ 1000
#define RSIZ 1000


struct filename		// structure used to store the name of all the files present in the directory.
{
	char fname[100];
	int length;
};


typedef struct filterfile	// structure used to store the name of only .txt files present in the directory.
{
	char filename[100];
	int status;
}FF;


typedef struct deletedfile	// structure used to store the name of duplicate .txt files
{
	char delfile[100];
}DF;


// Function Name: comparelinebyline()
// Description: this fucntion is used to compare the contents of the files
// Parameters: two file names
// Retrun value: returns 1 if content is same, otherwise 0

int comparelinebyline(char a[1000],char b[1000])   
{
    char line[RSIZ][LSIZ];
    char LINE[RSIZ][LSIZ];
    
    FILE *fptr = NULL,*FPTR=NULL;
    
    int i = 0,I=0;
    int tot = 0,TOT=0;
    
    fptr = fopen(a, "r");
    
    while(fgets(line[i], LSIZ, fptr))
{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;

    FPTR=fopen(b,"r");
    while(fgets(LINE[I], LSIZ, FPTR))
    {
        LINE[I][strlen(LINE[I]) - 1] = '\0';
        I++;
    }
    TOT = I;

    if(tot == TOT)
    {
        int flag=0;
        for(i=0,I=0 ;i<tot; i++)
        {
            if(strcmp(line[i],LINE[I])!=0)
            	flag=1;
            I++;
        }
        
        if(flag == 1)
            return 0;
        else
            return 1;

    }
    else 
    	return 0;
}


int main()
{
	struct filename arr[100];
	FF filter[100];
	DF del[100];
	
	int n = -1;
	int m = -1;
	int o = -1;
	int key;
	
	DIR *d;
	struct dirent *dp;
	d = opendir(".");
	
	if(d == NULL)
	{
		perror("");
	}
	else
	{
		printf("Files present in the directory: \n");
		for(;;)
		{
			dp = readdir(d);
			if(dp == NULL)
				break;
			n++;
			strcpy(arr[n].fname,dp->d_name);
			arr[n].length = strlen(arr[n].fname);
		}
		closedir(d);
	}

	for(int i=0; i<=n; i++)
	{
		printf("%s\n",arr[i].fname);
	}

	for(int i=0; i<=n; i++)
	{
		if(arr[i].fname[arr[i].length - 1] == 116)
		{
			if(arr[i].fname[arr[i].length - 2] == 120)
			{
				if(arr[i].fname[arr[i].length - 3] == 116)
        			{
            				if(arr[i].fname[arr[i].length - 4] == 46)
            				{
                 				m++;
                 				strcpy(filter[m].filename,arr[i].fname);
                 				filter[m].status=0;
            				}
        			}
    			}
		}
	}
	
	printf("\n\nNumber of text files present in the directory: ");
	printf("%d",m+1);
	printf("\nText files present are:\n\n");
	printf("\n");
	
	for(int i=0; i<=m; i++)
	{
		printf("%s\n",filter[i].filename);
	}
	
	for(int i=0;i<m;i++)
	{
	    if(filter[i].status == 1)
            {
            	continue;
            }
            
            else
            {
		for(int j=i+1;j<=m;j++)
        	    {
      			  filter[j].status = comparelinebyline(filter[i].filename,filter[j].filename);
      			  
      			  if(filter[j].status == 1)
      			  {
      			  	int inner_flag = 0;
      			  	
      			  	for(int x=0; x<=o;x++)
      			  	{
      			  		if(strcmp(filter[j].filename,del[x].delfile) == 0)
      			  			inner_flag = 1;
      			  	}
      			  	
      			  	if(inner_flag == 0)
      			  	{
      			  		o++;
      			  		strcpy(del[o].delfile,filter[j].filename);
      			  	}     		
      			  }
      			  
        	    }
            }
	}
	
	if(o < 0)
	{
		printf("No duplicate files present in the directory\n");
		return 1;
	}
	else
	{
		printf("\nDuplicate files present are:\n\n");
		for(int i=0; i<=o; i++)
    		{
   			printf("%s\n",del[i].delfile);
    		}
    	}
    	
    	printf("\nWould you like to delete all duplicate files?\nPress 1 if yes, otherwise 0: ");
    	scanf("%d",&key);
    	if(key == 1)
    	{
    		for(int i=0; i<=o; i++)
    		{
    			remove(del[i].delfile);
    		}
    		printf("Files have been removed.\nThank you.\n");
    	}
    	else
    		printf("Files have not been removed.\nThank you.\n");
    		  	
	return 0;
}

