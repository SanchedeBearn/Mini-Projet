// inclusion des fonctionnalité
#include <SFML/Graphics.hpp>
#include "Event.h"
#include<iostream>
#include "Stat.h"
#include "TexteSaisie.h"
#include "Texte_A_Recopier.h"
#include <string>
#include <vector>

// Pour pas écrire sf::
using namespace sf;
using namespace std;


int main()
{
	//création fenetre avec taille, bit et titre
	RenderWindow window(VideoMode(1920, 1080), "Monkey D. Type");

	// Activation du vsync
	window.setVerticalSyncEnabled(true);

	//MUSIQUE
	Music music;
	LoadMusic(music);
	//LOAD GAME MUSIC
	//music.play();


	// Partie Texte
	Font font;
	LoadFont(font);
	TexteSaisie saisie_correcte;
	int lettre = 0;
	int compteur_mot = 0;
	string mot_actuel = "";
	int bons_mots = 0;
	int mauvais_mots = 0;
	//CHARGEMENT BIBLIO
	//TEST POUR AFFICHER DU TEXTE AVEC LA FONCTION RANDOM ET LA BIBLIO
	Texte_A_Recopier Texte(font);
	vector<string> lines;
	biblio(lines);
	chargerTexteRec(saisie_correcte, lines, font);
	Text blob = saisie_correcte.getText();

	// Score
	Text score;
	score.setFont(font);
	score.setPosition(500, 500);


	//GAME CLOCK & TIMER
	Clock clock;
	Time duration = sf::seconds(30); // minuteur de 30 secondes
	int a = 0;
	//Partie Texte pour affichage timer
	Text TextTimer("Timer :", font, 32);
	TextTimer.setFillColor(Color(255, 255, 255, 125));
	TextTimer.setPosition(0, 0);

	//Bouton start
	Text start;
	RectangleShape button;
	Boutton(button, font, 900, 600, start);
	RectangleShape button2;
	Boutton(button2, font, 900, 600, start);
	button2.setFillColor(Color(100, 255, 100));

	Text retry;
	RectangleShape button3;
	BouttonRetry(button3, font, 900, 600, retry);



	//Score text
	Text Score("SCORE !", font, 40);
	Score.setPosition(900, 150);



	//POUR FAIRE UN TRUC QUI CLAQUE DE OUF
	//VISU ECRAN D'ACCEUIL
	Texture texturefond;
	loadtexture(texturefond);
	texturefond.setSmooth(true);

	Sprite fondecran;
	fondecran.setTexture(texturefond);


	//boucle qui tourne pour pas que la fenetre se ferme
	while (window.isOpen())
	{
		Event event;
		//boucle sur l'evenement event
		while (window.pollEvent(event))
		{
			//gestion input/event
			InputHandler(event, window);

			//Bouton surbrillance
			Vector2i mousePosition = Mouse::getPosition(window);
			if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
				if (a != 1 && a != 2) {
					a = 3;
				}
			}

			if (!button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
				if (a != 1 && a != 2) {
					a = 0;
				}
			}



			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					Vector2i mousePosition = Mouse::getPosition(window);
					if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						if (a != 2 && a != 1) {
							// button clicked!
							clock.restart();
							a = 1;
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					Vector2i mousePosition = Mouse::getPosition(window);
					if (button3.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						if (a != 0 && a != 3 && a != 1) {
							// button clicked!
							clock.restart();
							saisie_correcte.reset();
							lettre = 0;
							compteur_mot = 0;
							mot_actuel = "";
							bons_mots = 0;
							mauvais_mots = 0;
							biblio(lines);
							chargerTexteRec(saisie_correcte, lines, font);
							blob = saisie_correcte.getText();
							a = 0;
						}
					}
				}
			}




			if (event.type == sf::Event::Closed)
				window.close();

			if (a == 1) {

				if (event.type == sf::Event::TextEntered)
				{

					if (event.text.unicode != 13 && event.text.unicode != 8) // On évite la touche "retour arrière" et la touche "retour chariot"
					{
						string character(1, static_cast<char>(event.text.unicode));
						Text Textcharacter;
						Textcharacter.setString(character);

						//if (mot_actuel.size() < getNthWord(blob, compteur_mot).size())

						if (event.text.unicode == getNthWord(blob, compteur_mot)[mot_actuel.size()]) // Si le caractère tapé est correct: vert
						{
							saisie_correcte.setCharCol(lettre, Color::Green);
						}
						else // Si le caractère tapé est incorrect: rouge
						{
							saisie_correcte.setCharCol(lettre, Color::Red);;
						}


						/*
						if (saisie_correcte.getVect().size() < 1)
						{
							Textcharacter.setPosition(200, 500);
						}
						else if (saisie_correcte.getVect().size() > 0)
						{
							Text dernier_caractere = saisie_correcte.getVect()[lettre - 1];
							Textcharacter.setPosition(dernier_caractere.getPosition().x + dernier_caractere.getGlobalBounds().width, 500);
						}
						*/

						// Ajout du carcatère
						lettre++;
						mot_actuel = mot_actuel + character;
					}

					else if (event.text.unicode == 8) // Touche "Retour arrière"
					{
						if (saisie_correcte.getVect().size() > 0)
						{
							saisie_correcte.setCharCol(lettre, Color::White);
							mot_actuel = mot_actuel.substr(0, mot_actuel.size() - 1);
							lettre--;
						}
					}

					if (event.text.unicode == 32) // Barre espace
					{
						mot_actuel.pop_back();
						if (getNthWord(blob, compteur_mot) == mot_actuel) // Vérifie si c'était un bon mot
						{
							bons_mots++;
						}
						else {
							mauvais_mots++;
						}
						compteur_mot++;
						mot_actuel = "";
					}

				}

			}

		}

		//Partie Temps pour affichage timer
		Time elapsed = clock.getElapsedTime();
		Time remaining = duration - elapsed;
		float seconds = remaining.asSeconds();
		int milliseconds = remaining.asMilliseconds();

		Text remainingTimeText(to_string(seconds) + " s", font, 30);
		remainingTimeText.setFillColor(Color(255, 255, 255, 125));
		remainingTimeText.setPosition(0, 50);

		if (seconds < 0) {
			remainingTimeText.setString("Fin du temps !");
			if (a == 1) {
				a = 2;
			}
		}


		window.clear(Color::Black);
		window.draw(fondecran);
		if (a == 1) {
			window.draw(TextTimer);
			window.draw(remainingTimeText);
			saisie_correcte.afficherTexte(window);
			//window.draw(Texte.getText());
		}

		if (a == 0) {
			window.draw(button);
			window.draw(start);
			AffichageAcceuil(font, window);

		}

		if (a == 2) {
			score.setString("Nombre de mots corrects: " + to_string(bons_mots) + "/ Nombre de fautes: " + to_string(mauvais_mots));

			window.draw(TextTimer);
			window.draw(remainingTimeText);
			window.draw(score);
			window.draw(button3);
			window.draw(retry);
			window.draw(Score);

		}

		if (a == 3) {
			window.draw(button2);
			window.draw(start);
			AffichageAcceuil(font, window);
		}

		window.display();
	}

	//fin du programme
	return 0;
}
