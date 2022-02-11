#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int Ferry_cap = 0, Parking_cap=0, Total_cars=0,Temp_ferry_cap=0, Temp_parking_cap=0, Temp_cars=0, state = 1;
sem_t s; // Semaphore

void *Market_to_island()
{
	while(state)
	{
		if (Temp_cars < Total_cars)     // To check available cars.
		{
			if (Temp_parking_cap < Parking_cap)     // To Check Parking slots.
			{
				while(Temp_ferry_cap < Ferry_cap && Temp_parking_cap< Parking_cap && Temp_cars < Total_cars)  // To check ferry capacity.		
				{
					sem_wait(&s);       //To wait for a semaphore
					Temp_parking_cap++;
					Temp_cars++;
					Temp_ferry_cap++;
					sem_post(&s);       // To increase a value of semaphore
				} 		
				printf("MainLand to Island moved cars %d in the ferry.\n",Temp_ferry_cap);
				Temp_ferry_cap=0;
				sleep(4);
			}
		}
		else
		{
			printf("All available cars at Mainland are transferred from mainland to island in the ferry.\n");
			break;
		}
	}
}

 
void *Island_to_market()
{
	while(state)
	{		
		if (Temp_cars < Total_cars) 
		{			
			int Return_carCount = 0; 
			if(Temp_parking_cap == Parking_cap)
			{
				while(Return_carCount <=0)  				//random number of Total_cars to return
				Return_carCount = rand() % Ferry_cap  - 1; 
				sem_wait(&s);
				Temp_parking_cap = Temp_parking_cap - Return_carCount;
				sem_post(&s);
			}
			printf("Island to MainLand moved cars %d in the ferry.\n",Return_carCount);
			sleep(4);
		}
		else
			break;
	}
}

// Main function
int main(int argv, char* argc[])
{
	printf("Total cars at MainLand? : \n");
	scanf("%d", &Total_cars);
	
	printf("\nCapacity of Ferry? : \n");
	scanf("%d", &Ferry_cap);
		
	printf("Parking Capacity at Island? : \n");
	scanf("%d", &Parking_cap);
		
	sem_init(&s, 0, 1);		// Initialise semaphore 
	pthread_t marketToIsland,islandToMarket;
	
	// Creating two Thread
	pthread_create(&marketToIsland, NULL, &Market_to_island, NULL);
	pthread_create(&islandToMarket, NULL, &Island_to_market, NULL);
	pthread_join(marketToIsland,NULL); 
	pthread_join(islandToMarket,NULL);
		
	// Destroing semaphore
	sem_destroy(&s);
	return 0;
}
