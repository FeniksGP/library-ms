#include "./data.h"

const std::string text[] = {"Version: 1.0.0", "library-ms [-v | --version | -h | --help] operation type arguments\n-h, -help\n	"
"Pokazuje krotka informacje o programie.\n-v, --version\n	Wypisuje aktualna wersje programu.\n\noperation\n	Wybor operacji. Dostepne sa:\n"
"	list - wypisuje zawartosc\n	add - dodaje obiekt do bazy danych (dla book argumenty to: tytul autor ilosc_ksiazek) (dla user argumenty to: imie nazwisko)"
"\n	remove - usuwa obiekt z bazy danych (dla book tytul autor) (dla user imie nazwisko)\n"
"	modify - zmienia obiekt w bazie danych (dla book tytul autor ilosc_ksiazek_do_zmiany tytul_do_zmiany autor_do_zmiany) "
"(dla user imie nazwisko imie_do_zmiany nazwisko_do_zmiany)\n	borrow - pozycza uzytkowikowi ksiazke (tylko dla user imie nazwisko tytul autor)\n"
"	get - odbiera ksiazke od uzytkownika (tylko dla user imie nazwisko tytul autor)\n\n	type - okresla czy ma wykonac operacje dla uzytkownika (user) czy dla"
" biblioteki (book)\n", "Podano zly argument.\nAby dowiedziec sie jak program dziala wpisz 'library-ms -h'.",
"Pomyslnie dodano ksiazke.", "Podana ksiazka istnieje w bibliotece.", "Pomyslnie usunieto ksiazke.", "Podana ksiazka nie istnieje w bibliotece.",
"Pomyslnie zmodyfikowano ksiazke.", "Pomyslnie dodano uzytkownika.", "Podany uzytkownik istnieje w bazie.", "Pomyslnie usunieto uzytkownika.", 
"Podany uzytkownik nie istnieje w bazie.", "Pomyslnie zmodyfikowano uzytkownika.", "Nie ma wystarczajacej ilosci ksiazek.", 
"Uzytkownik nie posiada podanej ksiazki.", "Pomyslnie oddano ksiazke", "Pomyslnie pozyczono ksiazke uzytkownikowi."};
const std::string errors[] = {"Nie udalo sie otworzyc bazy danych.", "Nie udalo sie edytowac bazy danych.", "Blad operacji plikow."};
