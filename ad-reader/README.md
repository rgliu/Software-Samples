
## I've included the binary, which you can run using 

./adProject ads.txt requests.log > output.txt

## To build using command line

cmake -B build  
make -C build  
cp ./build/ 
./adProject ads.txt requests.log > output.txt  

## The executable takes two arguments  
    1. input ads file path (ads.txt)   
    2. requests file path (requests.log)  

## In addition to the original requests.log, I've also included 2 request files 
    - requestsWithExchange2Format.log contains the same info as requests.log, except with the Part II domain (simpli.fi).  
    - requestsWithMultiple.log is the original requests.log with 2 instances of the simpli.fi request mixed in  

**Design doc included (designDoc.pdf)**
