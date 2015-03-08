;*------------------------------------------------------------------------
;*MODULE                      TP2 - machine pgcd
;*------------------------------------------------------------------------
;* Auteur(s) : BLIN Sébastien /COLLIN Pierre-Henri   
;*
;* Formation :   ESIR1            Groupe: 2
;*-------------------------------------------------------------------------
;*OBJET
;*      Ce programme permet de lire une suite de couples d'entiers,
;*      et de calculer le pgcd de chaque couple
;*
;*     le programme s'arrette sur la lecture d'un entier egal a 0
;*POINTS d'ENTREE
;*      neant (programme principal)
;*DONNEES EXPORTEES
;*      neant
;*REFERENCES EXTERNES
;*      neant
;*--------------------------------------------------------------------------
;*SOUS-PROGRAMMES :
;*      LIRENT   : lit un entier de deux chiffres en base 10
;*      ECRIRENT : ecrit un entier de deux chiffres en base 10
;*      PGCD     : calcule le PGCD de deux entiers
;*-------------------------------------------------------------------------
.model SMALL
.stack 
.data
BIENVENUE			DB	'TP2 - Calcul de PGCD (00 pour quitter) $'
MSG						DB	13, 10, 'Entrez un nombre ', 13, 10, '$'
BASED					DB	13, 10, 'Nombre en base 10 ', 13, 10, '$'
MSGP					DB 	13, 10, 'Le pgcd de ', '$'
MSGP2					DB 	' et ', '$'
MSGP3					DB 	' est :', 13, 10, '$'
.code

printMSG PROC
							MOV		AH,9h
							INT		21H
							RET
printMSG ENDP

start :				MOV 	AX,@data
							MOV 	ds,AX
							MOV		DX,OFFSET BIENVENUE
							CALL	printMSG
MAIN:
							CALL	lecture																		; Lecture du premier nombre
							CMP		AL,0																			; Si nombre = 0, alors quitter
							JE 		FMAIN
							PUSH 	AX																				; On sauvegarde dans la pile le premier nombre
		
							MOV		DX,OFFSET BASED														; Affichage du nombre
							CALL	printMSG
							CALL	affichage
		
							CALL	lecture																		; Lecture du premier nombre
							CMP		AL,0																			; Si nombre = 0, alors quitter
							JE		FMAIN
							PUSH	AX																				; On sauvegarde dans la pile le premier nombre
							MOV		DX,OFFSET BASED														; Affichage du nombre
							CALL	printMSG
							CALL	affichage
							
							POP		BX																				; Récupération des valeurs pour l'affichage
							POP		AX
							PUSH 	BX																				; Sauvegarde pour le calcul du PGCD
							PUSH 	AX
		
							MOV		DX,OFFSET MSGP														; Affichage du message Le pgcd de ... et de ... est
							CALL	printMSG		
							POP		AX
							MOV		CX,AX
							CALL 	affichage
							MOV		DX,OFFSET MSGP2
							CALL	printMSG
							POP		AX
							PUSH 	AX
							PUSH 	CX
							CALL 	affichage
							MOV		DX,OFFSET MSGP3	
							CALL	printMSG
		
							POP		BX																				; Calcul du pgcd et affichage
							POP		AX
							CALL 	pgcd
							MOV 	AL,CL
							CALL 	affichage
							JMP 	MAIN
FMAIN:				JMP		fin
;*------------------------------------------------------------------------
;*SOUS-PROGRAMME      LIRENT
;*------------------------------------------------------------------------
;*SPECIFICATION
;*  lit un nombre de deux chiffres en base 10 et rend le resultat de sa
;*  conversion en base 2
;*  La donnee est supposee correcte
;*
;*PASSAGE DES PARAMETRES
;*   RESULTAT : AL = vALeur du nombre en base 2
;*-------------------------------------------------------------------------
lecture PROC
							MOV		DX,OFFSET MSG	
							CALL	printMSG

							MOV 	AH,1h																			; Lecture du premier chiffre
							INT 	21h 
							MOV 	CH,AL 	
							MOV 	AH,1h																			; Lecture du second chiffre
							INT 	21h		
							MOV 	CL,AL

							SUB 	CL,30h																		; On déplace les 2 octets du nombre BX
							SUB 	CH,30h																		; dans AL (en base 2)
							MOV 	AL,10																			; Les dizaines
							IMUL 	CH
							ADD 	AL,CL 																		; les unités
							RET
lecture ENDP
;*------------------------------------------------------------------------
;*SOUS-PROGRAMME       ECRIRENT
;*------------------------------------------------------------------------
;*SPECIFICATION
;*   convertit une valeur binaire <=99 en base 10,et affiche le resultat
;*   a l'ecran. Cette valeur est supposee etre <=99
;*
;*PASSAGE DES PARAMETRES
;*   ENTREE : AL = valeur a afficher en base 2
;*-------------------------------------------------------------------------
affichage PROC
							MOV 	AH,0
							MOV 	BL,10
							IDIV 	BL																				; Dans AH on place les dizaines, AL les unités
							MOV 	BX,AX
		
							ADD		BL,'0'  																	; On transforme en chiffre affichable
							ADD		BH,'0'		
							MOV		DL,BL   																	; On affiche
							MOV 	AH,2H
							INT 	21h		
							MOV		DL,BH 
							MOV 	AH,2H
							INT 	21h
							RET
affichage ENDP
;*---------------------------------------------------------------------------
;*SOUS-PROGRAMME      PGCD
;*---------------------------------------------------------------------------
;*SPECIFICATION
;*   calcule le PGCD de deux entiers >0

;*PASSAGE DES PARAMETRES
;*   ENTREE : AL = entier n1
;*            BL = entier n2
;*
;*   RESULTAT : CL = pgcd(n1,n2)
;*---------------------------------------------------------------------------
pgcd PROC
lopp:		    	CMP  	BL,AL																			; Tant que BL != AL
         			JE    fin_loop
         			CMP   AL,BL     																; Si A > B
         			JG    AGreaterB																	; A-=B
        		 	SUB   BL,AL																			; Sinon B-=A
       			  JMP   lopp         
AGreaterB: 		SUB 	AL,BL
           		JMP 	lopp         
fin_loop: 	  MOV 	CL,AL																			; Sauvegarde
           		RET
pgcd ENDP

fin:					NOP																							; fin du programme
							MOV 	AX,4c00h
							INT 	21h
							end 	start
