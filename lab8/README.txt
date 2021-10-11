Am facut urmatoarele modificari in cele 2 fisiere:

	Fisierul client.c: 	

	Cu functia select din interiorul while-ului din client se controleaza descriptorul din care se realizeaza citirea.
Daca descriptorul STDIN_FILENO este in setul tmp_fds, atunci acesta se trimite la server, daca nu este un mesaj de iesire.
Daca descritorul socket-ului este in tmp_fds, atunci se asteapta primirea unui mesaj, ce se afiseaza ulterior. Astfel este 
realizata interactiunea user, server.

	Fisierul server.c:

	Daca se primeste un mesaj de lungime 0, atunci s-a terminat trimiterea. Altfel, se trimite mesajul la
clientul corespunzator.