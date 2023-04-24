#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "TexteSaisie.h"

using namespace sf;
using namespace std;

void InputHandler(Event event, Window& window);
void LoadFont(Font& font);
void LoadMusic(Music& music);
void Boutton(RectangleShape &button,Font& font, int buttonX, int buttonY, Text& start);
void AffichageAcceuil(Font& font, RenderWindow& window);
int generateRandomNumber();
void biblio(vector<string>& lines);
void chargerTexteRec(TexteSaisie& Texte, vector<string>& lines, Font& font);
int count_letters(string word);
string getNthWord(Text &texte, int n);
void loadtexture(Texture& texture);
void BouttonRetry(RectangleShape& button, Font& font, int buttonX, int buttonY, Text& retry);