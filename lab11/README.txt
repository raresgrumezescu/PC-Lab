fisierul send_mail.c:
	Se creeaza un socket clientului TCP, apoi se completeaza compul acestuia de adresa
	sockaddr_in cu portul si adresa IP a serverului. (port = SMTP_PORT).
	Se realizeaza conexiunea la srver prin socket-ul creat la punctele anterioare;
	apoi se asteapta un mesaj de conectare de la server, afisandu-se ulterior in
	terminal.
	Se trimit comenzile: HELO, MAIL FROM, RCPT TO si DATA.
	In final, se trimite mail-ul: se trimit antetele, corpul si atasamentul.
	Dupa ce aceasta operatiune ia sfarsit, se trimite comanda QUIT si se inchide socket-ul
	de care ne-am folosit pentrui a trimite mail-ul.