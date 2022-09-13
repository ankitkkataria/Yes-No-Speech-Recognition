#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int maximum(FILE *fp);
int main (){
    FILE *fp; //This is the file pointer
    long * wave_energy; // This is a pointer for me to store an array which contains the energy of every hundred samples for entire file
    long * wave_zcr;    // This is a pointer for me to store an array which contains the zcr of every hundred samples for entire file
   /* In the fopen below put in the file name along with .txt extension 
    this is the file that will be checked for whether it's a yes or a no*/
    fp=fopen("3rdmyno.txt","r");
    if (fp==NULL)
    {
        printf("This file is not available");
    }
   else 
    {  
        int max=maximum(fp); // this finds the max in file
        rewind(fp); // to reset the pointer after finding max
        int tempvalues[100]; // every hundered values i will store here
        long  temp_energy_values[100]; // this will contain squares for every value xi
        /*I'm declaring this x so i can finally store the value of energy
         and zcr for every hundred samples in wave_energy and wave_zcr array*/
        static int x = 0;
        int sample = 0;//this variable will finally contain number of samples in the file
        char arr[100]; // this is just a temporary array
        /*this fscanf is used so the meta data on top of the file we can automatically 
           read no of samples and we don't have to go and manually delete the meta data out of each file*/
        fscanf(fp,"%s        %d\n",arr,&sample ); 
        for(int i =0;i<=3;i++)// this for loop just skips the next three lines in metadata
        {
            fgets(arr,100,fp);
        }
        sample/=100; // this is so i can make array for final wave_energy and wave_zcr 
        wave_energy = new long[sample];
        wave_zcr = new long[sample];
        while (!feof(fp)) // this while loop puts energy per 100 samples in wave_energy and zcr in in wave_zcr
        {
            static long  energy_of_hundred_samples=0;
          
            for (int i=0;i<100;i++) // this just reads 100 values moving forward
            {
                fscanf(fp,"%d\n",&(tempvalues[i])); 
                if(feof(fp))
                {
                    break;
                }
            
            }
            
            
            for(int i=0;i<100;i++) // this first normalizes and and then sqaure each value and puts it in temp_energy_values
            {
                tempvalues[i]=(tempvalues[i]*5000/max);
                temp_energy_values[i]=tempvalues[i]*tempvalues[i];
            }   
            
            long energy_of_hundred_total = 0;   
            // Let's calculate energy of first hundred samples 
            for (int i =0; i<100;i++) // this is so i can calculate the energy per hundred samples
            {
                
                energy_of_hundred_total += temp_energy_values[i];
                energy_of_hundred_samples = (energy_of_hundred_total/100);
                
            }   
         
            wave_energy[x] =energy_of_hundred_samples;   // this is storing the energy per hundred samples then x will move forward
                
          
            int zcr_for_hundred_samples = 0;   
            // let's calculate zcr for the per hundred samples   
            for(int i =0;i<99;i++){
                if(( (tempvalues[i] >0) && (tempvalues[i+1] < 0)) || ( (tempvalues[i] <0) && (tempvalues[i+1] > 0)))
                {
                    zcr_for_hundred_samples = zcr_for_hundred_samples+1;
                }
            }

            wave_zcr[x]=zcr_for_hundred_samples;  // again x will increment and store every zcr value per 100 samples
            x++; // incrementing x to make sure that we put energy and zcr per 100 samples in wave_energy and wave_zcr array 
         }
    
    
    
  FILE *seperate_file;                                      
  seperate_file  = fopen("Seperatefile.txt","w"); // making a seprate file to write the energy and zcr values per 100 samples
    if (seperate_file==NULL)
    {
        printf("This file is not available");
    }
    
    else 
    {
          for (int i=0;i<sample;i++)    
          {  

               fprintf(seperate_file,"these are the energies per hundred samples\n");  // nothing but writing energy values
               fprintf(seperate_file,"%d------%ld\n",i,wave_energy[i]); 
          }
         
        fprintf(seperate_file,"now these are the zcr values\n");
        
          for (int i=0;i<sample;i++) 
          {
             fprintf(seperate_file,"%d------%ld\n",i,wave_zcr[i]); // writing zcr values
          }
        

    }
    
    
 }
 
 int max_of_noise=0; // this will contain max of ambient noise

 /* this loop belows finds the maximum 
    energy in first 15 enerfy values */



for(int i=0;i<15;i++)
    {
    if(max_of_noise<wave_energy[i])
    {
        max_of_noise = wave_energy[i];
    }
    
    }

int starting_of_word=0; // this is so i can find the index of from where our word actually starts after ambient noise

    while(wave_energy[starting_of_word] <= (3*max_of_noise)) // if something has a energy three times larger then noise we think it's a word
    {
        starting_of_word++;
        
    }
int ending_of_word =starting_of_word;   // now from where we found the word we start looking for where it ends 
    while(wave_energy[ending_of_word] >= (3*max_of_noise)) // this will find the index for where the word ends
    {
        ending_of_word++;
    }

   ending_of_word--; // this is so we are at the end of word

int size_of_the_word = ending_of_word-starting_of_word+1; // this is the size of the word

int size_of_the_window = size_of_the_word*0.4; // this is so we can make a 40% window  

/*we will be taking average zcr of the last 40% of the zcr values 
in our word that's why we found from what index in wave_zcr we got the word and till where
now all that below is for that purpose*/


int average_of_zcr=0; 
    for(int i = ending_of_word; i>((ending_of_word)-(size_of_the_window));i--) // what this loop does is from the index where the word ends we come back till 40% of our word 
    {
        average_of_zcr+=wave_zcr[i];
    }

average_of_zcr/=size_of_the_window; // we got the average of the last 40% of our word

// if that zcr value is less then 20 then it's a vowel so it's a no else it's a yes this is cause fricatives sounds liks ssss at the end of yes tend to have high zcr
if(average_of_zcr>20)
{
    printf("it's a yes");
    
    
}

else {
    printf("it's a no ");
    
    
}


   return 0;
 
}

/*This is so i can find the maximum sample in the 
entire file that's the purpose of this function*/

    
    
int maximum(FILE *fp) {
    static int maxx;
   
        char arr[100];                   // this for loop allows us to skip the meta data first 4 lines i mean
        for(int i =0;i<=4;i++)
        {
            fgets(arr,100,fp);
        }
        
        
        int temp = 0;
        while (!feof(fp)) // finding max
        {
             fscanf(fp,"%d",&temp);
             if (maxx<temp) maxx = temp;
        }
        
          return maxx; 
    


                         }

    