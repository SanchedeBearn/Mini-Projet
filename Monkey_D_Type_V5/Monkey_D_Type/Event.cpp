#include <SFML/Graphics.hpp>
#include "Event.h"
#include <iostream>
#include "Stat.h"
#include "TexteSaisie.h"
#include "Texte_A_Recopier.h"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // pour rand() et srand()
#include <ctime>   // pour time()
#include <set>


using namespace std;
using namespace sf;


//fermer la fenetre en appuyant sur la croix
void InputHandler(Event event, Window& window)
{
	if (event.type == Event::Closed)
	{
		window.close();
	}
}

//charger police d'écriture
void LoadFont(Font& font)
{
	if (!font.loadFromFile("Res/Poppins-Regular.ttf"))
	{
		//si erreur
		cout << "erreur chargement police" << endl;
	}
}

void LoadMusic(Music& music)
{
	if (!music.openFromFile("Res/one-piece-générique-nouvelle-saison.ogg")) {
		std::cerr << "No music file found!" << std::endl;
	}
}


void Boutton(RectangleShape& button, Font& font, int buttonX, int buttonY, Text& start)
{
	button.setSize(Vector2f(200, 100));
	button.setPosition(buttonX, buttonY);
	button.setFillColor(Color::Green);
	start.setFillColor(Color::White);
	start.setCharacterSize(40);
	start.setString("START");
	start.setFont(font);
	start.setPosition(buttonX + 40, buttonY + 25);
}

void AffichageAcceuil(Font& font, RenderWindow& window) {
	Text Titre("MONKEYTYPE by Sanche et Logan", font, 50);
	Titre.setPosition(600, 100);
	Titre.setFillColor(Color::White);
	Titre.setStyle(Text::Bold | Text::Italic | Text::Underlined);

	Text Version("version 1.3", font, 20);
	Version.setPosition(1700, 900);
	Version.setFillColor(Color::Yellow);

	Text Pres1(" Envie de tester votre rapidité ? Pas de probleme nous avons pensé à vous !", font, 30);
	Pres1.setPosition(400, 300);
	Pres1.setFillColor(Color::White);

	Text Pres2(" Avec notre MONKEYTYPE, venez tester votre vitesse de frappe sur des mots aléatoire !", font, 30);
	Pres2.setPosition(350, 340);
	Pres2.setFillColor(Color::White);

	Text Pres3(" made by Sanche De Bearn and Logan BAUDINO", font, 30);
	Pres3.setPosition(600, 380);
	Pres3.setFillColor(Color::White);


	window.draw(Titre);
	window.draw(Version);
	window.draw(Pres1);
	window.draw(Pres2);
	window.draw(Pres3);
}

//POUR DICTIONNAIRE ET AFFICHER TEXTE


int generateRandomNumber()
{
	int m = 0;
	int n = 0;
	int p = 0;
	m = rand() % 32358;// génère un nombre aléatoire entre 0 et 323578
	n = rand() % 10;
	p = m * n;
	return p;
}

void biblio(vector<string>& lines)
{

	// ouvre le fichier en lecture
	ifstream infile("Res/Biblio.txt");

	// vérifie si le fichier est ouvert avec succès
	if (!infile.is_open()) {
		cerr << "Erreur: impossible d'ouvrir le fichier." << endl;
	}

	// lit le fichier ligne par ligne et stocke chaque ligne dans le vecteur
	string line;
	while (getline(infile, line)) {
		lines.push_back(line);
	}

	// affiche le contenu du vecteur (chaque ligne)

	// ferme le fichier
	infile.close();

}

void chargerTexteRec(TexteSaisie& Texte, vector<string>& lines, Font& font)
{
	Texte.reset();
	srand(time(0));

	for (int i = 0; i < 7; i++) {
		Text nouveau_mot;
		Text dernier_caractere;
		int taille;
		nouveau_mot.setString(lines[generateRandomNumber()]);
		for (int j = 0; j < nouveau_mot.getString().getSize(); j++)
		{
			Text nouvelle_lettre;
			nouvelle_lettre.setString(nouveau_mot.getString()[j]);
			nouvelle_lettre.setFont(font);
			nouvelle_lettre.setFillColor(Color::White);
			nouvelle_lettre.setCharacterSize(30);
			if (Texte.getVect().size() < 1)
			{
				nouvelle_lettre.setPosition(200, 500);
			}
			else if (Texte.getVect().size() > 0)
			{
				taille = Texte.getVect().size();
				dernier_caractere = Texte.getVect()[taille - 1];
				nouvelle_lettre.setPosition(dernier_caractere.getPosition().x + dernier_caractere.getGlobalBounds().width, 500);
			}
			Texte.addchar(nouvelle_lettre);
		}
		Text espace;
		espace.setString(" ");
		espace.setFont(font);
		espace.setFillColor(Color::White);
		espace.setCharacterSize(30);
		taille = Texte.getVect().size();
		dernier_caractere = Texte.getVect()[taille - 1];
		espace.setPosition(dernier_caractere.getPosition().x + dernier_caractere.getGlobalBounds().width, 500);
		Texte.addchar(espace);
	}
}


int count_letters(string word) {
	int count = 0;
	for (char letter : word) {
		if (isalpha(letter)) { // Vérifie si la lettre est une lettre de l'alphabet
			count++;
		}
	}
	return count;
}

string getNthWord(Text &texte, int n) {
	string str = texte.getString();
	string word;
	int word_count = 0;
	size_t pos = 0;

	while (pos < str.size()) {
		// Ignore les espaces
		while (pos < str.size() && str[pos] == ' ') {
			pos++;
		}

		// Si on est à la fin de la chaîne, sortir de la boucle
		if (pos == str.size()) {
			break;
		}

		// Trouve la fin du mot courant
		size_t end_pos = pos;
		while (end_pos < str.size() && str[end_pos] != ' ') {
			end_pos++;
		}

		// Si on a trouvé le n-ième mot, le retourner
		if (word_count == n) {
			return str.substr(pos, end_pos - pos);
		}

		// Sinon, continuer à chercher le mot suivant
		word_count++;
		pos = end_pos;
	}

	// Si le n-ième mot n'existe pas, renvoyer une chaîne vide
	return "";
}

void loadtexture(Texture& texture) {
	if (!texture.loadFromFile("Res/backgroundnoir3.jpg"))
	{
		//si erreur
		cout << "erreur chargement texture" << endl;
	}
}

void BouttonRetry(RectangleShape& button, Font& font, int buttonX, int buttonY, Text& retry)
{
	button.setSize(Vector2f(200, 100));
	button.setPosition(buttonX, buttonY);
	button.setFillColor(Color::Green);
	retry.setFillColor(Color::White);
	retry.setCharacterSize(40);
	retry.setString("RETRY");
	retry.setFont(font);
	retry.setPosition(buttonX + 40, buttonY + 25);
}