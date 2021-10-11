requests.c:
	*compute_get_request(): Se salveaza in line fie url-ul fie url-ul si parametrii 
		queriului, in functie de valoarea lui query_params. Se apeleaza apoi functia
		compute-message(), prima data cu line pastrand informatiile
		specificate anterior, iar a doua oara cu numele hostului. Se adauga
		headerele si cookie-urile in conformitate cu formatul protocolului. Aceste
		informatii sunt retinute in variabila line, care, dupa ce sunt adaugate,
		se da ca parametru functiiei compute_message. In final se mai adauga si
		un newline iar mesajul se returneaza.
	*compute_post_request(): functia este asemanatoare ca structura cu precedenta. 
		Se apeleaza compute_message progresiv, intai cu numele metodei, URL si host,
		apoi cu headerele si cookie-urile, iar apoi cu un newline. Difera faptul ca
		la mesaj se pune si payload-ul salvat in body_data_buffer.

clients.c:
	Ex1: se deschide o conexiune si se trimite mesajul message la server, folosindu-se 
	socket-ul creat. Se asteapta raspunsul serverului si se afiseaza

	Ex2: se trimit la server username si parola, si se afiseaza raspunsul primit.

	Ex3: se face rost de weather key de la server, asteptand-o in raspunsul dat.

	Ex4: Se obtine aceeasti weather key, dar nu de la server, ci de la API-ul
	corespunzator. 

	Ex6: Se face delogarea de la server. La final, se inchide socket-ul.

	