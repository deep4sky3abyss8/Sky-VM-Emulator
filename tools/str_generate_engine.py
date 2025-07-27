from colorama import Fore , init
import random
import os
init()
conted = 1 
while conted :
    
    while True :
        try :
            reg = int(input(Fore.YELLOW+"\n>>> Enter Register Index/Number between 0-100 : "+Fore.RESET))
            if 0<=reg<=100 :
                break
            print(Fore.RED+f"\n[!] InputError  Code{random.randint(0,10000)} : Invalid input as < index >"+Fore.RESET)
        except :
            print(Fore.RED+f"\n[!] InputError  Code{random.randint(0,10000)} : Invalid input as < index >"+Fore.RESET)
        
        
    while True :
        color = input(Fore.YELLOW+">>> Enter Color You Want [blue/red/green/yellow] : "+Fore.RESET)
        if (' ' not in color) and (color.upper() in ("BLUE","RED","GREEN","YELLOW")) :
            color = color[0].upper()
            break
        print(Fore.RED+f"\n[!] InputError  Code{random.randint(0,10000)} : Invalid input as < color >"+Fore.RESET)
        
        
    string = input(Fore.YELLOW+">>> Enter Your Str ( terminate by Enter ) : "+Fore.RESET)
    print("\n\n>>> Your Str Disassembly Printing Code\n"+Fore.GREEN)
    # ASSN 8 Y
    # PUTC 8
    
    
    print(20*"=",f"\nCTCT {color}")
    for letter in string :
        print(f"ASSN {reg} {ord(letter)}")
        print(f"PUTC {reg}")
    print("CTCT 0",20*"=",sep='\n')
    print(Fore.RESET+"\n\n\n>>> Copy Your Output ...\n")
    while True :
        try :
            conted = int(input(f">>> Press ...\n\n\t[ 1 ] to input again\n\t[ 0 ] to exit\n\n>>> Your Choise : "))
            if conted==1 or conted==0 :
                break
            print(Fore.RED+f"\n[!] InputError  Code{random.randint(0,10000)} : Invalid input as < choise >"+Fore.RESET)
        except :
            print(Fore.RED+f"\n[!] InputError  Code{random.randint(0,10000)} : Invalid input as < choise >"+Fore.RESET)
os.system("cls"or"clear")

# Created by mMahdi in 7/27/2025 - 12:27

