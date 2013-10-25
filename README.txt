Student : Ionescu Eugen-Andrei
Grupa : 332CA


				Tema4 - EGC


================================================================================
		1. Prezentarea Temei

	
   - Nava

     Nava este generata din fisierul "ship_file.off" - unul din fisierele 
   disponibile ca exemplu
     Pentru citirea fisierului am utilizat portiuni din codul gasit la link-ul
   specificat in enunt (s-a precizat pe forum)

   - Scutul
     
     Scutul este creat folosind glutSolidSphere() in centurl navei.
     Acesta sufera aceleasi translatii ca si cele ale navei.
     Transparenta este obtinuta prin  blending.

   - Asteroizii

     Asteroizii sunt creati folosind glutSolidDodecahedron() si se deplaseaza 
   pe axa OX intre marginile scenei.
     Viteza si dimensiunea acestora este generata aleator.
   
     La orice moment se gasesc un numar fix (n) de asteroizi in scena.Acestia 
   sunt stocati intr-un vector de obiecte de tip asteroid.
     Daca un asteroid este "distrus" (iese din scena , intra in contact cu scutul
   navei sau sunt folosite tunurile laser)  , acesta apare la marginea scenei 
   cu caracteristici aleatoare.  
     
   - Camera
     Camerele folosite sunt cele 3 precizate in enunt
     Camera dinamica si cea a de la bordul navei se pot deplasa pe cele 
   trei axe de coordonate.
     Camera navei se misca odata cu nava.

     Camera asteroid se activeaza apasand tasta '3' si selectand un asteroid.
   Aceasta se orienteaza spre nava si se deplaseaza impreuna cu asteroidul.

   - Lumini

     Am folosit 2 surse de lumina ambientala :  una alba , si celalta albastruie

     Mai exista 2 lumini de tip spot in stanga si in dreapta navei cu unghi de cutoff
     de 35 de grade.

   - Picking

     Pentru Picking am folosit codul din laboratorul 7
 	
   - Coliziuni

     Pentru fiecare asteroid se verifica distanta intre acesta si nava. 
     Daca distanta este mai mica decat dimensiunea asteroidului + raza scutului
   Asteroidul este resetat si scutul scade cu o unitate
     Cand scutul ajunge la 0  acesta dispare si urmatoarea coliziune termina jocul

    * Ecran  "GAME OVER" neimplementat     		

	

================================================================================
		2. Controlul Jocului

Taste: 

'1' : camera dinamica
'2' : camera nava
'3' : intra in modul de selectie pt camera asteroid

'w , s ' : deplasarea camerei dinamice inainte si inapoi (OZ)
'a , d ' : deplasarea camerei dinamice stanga si dreapta (OX)
'r , t ' : deplasarea camerei dinamice sus si jos (OY)


'i , k ' : deplasarea navei si camerei nava inainte si inapoi
'j , l ' : deplasarea navei si camerei nava stanga si dreapta
'p , ; ' : deplasarea navei si camerei nava sus si jos

 * directile de deplasare sunt din perspectiva FPS


'q'  : opreste luminile ambientale





================================================================================
		3. Probleme Intalnite

 I. Generarea asteroizilor
   - aici am intalnit o problema cand am incercat sa generez la momente aleatoare 
   un asteroid nou cu caracteristici random.
   Am solutionat aceasta problema folosind un vector de  n asteroizi.
   Cand asteroidul "i" dispare din scena  , acesta este refacut folosind 
   randomize_asteroid() in partea din stanga a scenei.

 II. Picking in first-person 

   - Am avut cateva probleme cu selectarea obiectelor in  modul FPS.

   Solutia folosita a fost cea propusa pe forum . 
   In momentul in care se face picking scena este desenata fara scut.



================================================================================


