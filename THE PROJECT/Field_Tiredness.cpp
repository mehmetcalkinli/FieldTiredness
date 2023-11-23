#include <iostream>
#include <fstream>
#include <string>
#include <sstream>




struct Field 
{
    int sizeX;
    int sizeY;
};
struct PlantingCount
{
    int count;
};
struct Coord
{
    int startXCoord;
    int startYCoord;
    int endXCoord;
    int endYCoord;
};


int main()
{ 
    std::string fileName;
    std::cout << "Enter file name without space and without quotient mark and add .txt at the end of the name of the file: ";
    std::cin >> fileName;

    struct Field field;
    struct PlantingCount plantingCount[2020];
    struct Coord coord[2020][10];

    int minYear = 0;
    int maxYear=0;
    int pci = 0; //planting count index

    

    
    int tirednessMap[40][40];
    int updatedTirednessMap[40][40];

    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            tirednessMap[i][j] = 0;
        }
    }

    
    int nYear = 0; 
    int nCount = 0;
    
    int readValue = 0;

    
    std::string inputString;
    


    std::ifstream inputFile;
    inputFile.open(fileName);
    

    if (inputFile.is_open()) 
    {
        int i = 0;   //input index
        while (!inputFile.eof())
        {
            
            inputFile >> inputString;
            
            if (i==0) 
            {
                field.sizeX= stoi(inputString);
            }
            else if (i == 1)
            {
                field.sizeY = stoi(inputString);
            }
            else 
            {
                readValue = stoi(inputString);
                if (readValue >1000)
                {
                    nYear = readValue;
                    if (minYear==0) 
                    {
                        minYear = nYear;

                    }
                    if (maxYear ==0 || minYear< nYear)
                    {
                        maxYear = nYear;
                    }
                   
                    inputFile >> inputString;
                    nCount= stoi(inputString);
                    readValue = nCount;
                    plantingCount[nYear].count = readValue;
                   
                    pci=1;
                }
                else
                {
                    if (pci<=nCount) 
                    {
                        coord[nYear][pci].startXCoord = readValue;

                        inputFile >> inputString;
                        readValue = stoi(inputString);
                        coord[nYear][pci].startYCoord = readValue;

                        inputFile >> inputString;
                        readValue = stoi(inputString);
                        coord[nYear][pci].endXCoord = readValue;


                        inputFile >> inputString;
                        readValue = stoi(inputString);
                        coord[nYear][pci].endYCoord = readValue;

                        pci++;
 
                    }
                
                }
            }

            
            i++;
            
        }
        inputFile.close();


        for (int i = minYear; i <= maxYear; i++)
        {
            for (int i = 0; i < field.sizeX; i++)
            {
                for (int j = 0; j < field.sizeY; j++)
                {
                    updatedTirednessMap[j][i] = -1;
                }
            }

            if (plantingCount[i].count==0)
            {
                for (int i = 0; i < field.sizeX; i++)
                {
                    for (int j = 0; j < field.sizeY; j++)
                    {
                        if (tirednessMap[j][i] > 0)
                        {
                            tirednessMap[j][i] += -1;
                        }
                        
                    }
                }
            }
            else
            {
              
                for (int j = 1; j <= plantingCount[i].count; j++)
                {
                    for (int x = coord[i][j].startXCoord; x <= coord[i][j].endXCoord; x++)
                    {
                        for (int y = coord[i][j].startYCoord; y <= coord[i][j].endYCoord; y++)
                        {

                            updatedTirednessMap[y][x] = 1;
                        }
                    }
                }
                for (int x = 0; x < field.sizeX; x++)
                {
                    for (int y = 0; y < field.sizeY; y++)
                    {
                        if (updatedTirednessMap[y][x]==1)
                        {
                            tirednessMap[y][x] += updatedTirednessMap[y][x];
                        }
                        else if (updatedTirednessMap[y][x] == -1)
                        {
                            if (tirednessMap[y][x]>0)
                            {
                                tirednessMap[y][x] += updatedTirednessMap[y][x];
                            }
                        }
                    }


                }
                
            }
        }

    }
    
    
    
    
    


    for (int y = 0; y < field.sizeY; y++)
    {

        for (int x = 0; x < field.sizeX; x++)
        {
            std::cout << tirednessMap[y][x];
        }
        std::cout << std::endl;
    }
    
    
    

    

}


