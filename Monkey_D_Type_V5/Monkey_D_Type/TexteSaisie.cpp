#include "Stat.h"
#include "Event.h"
#include "TexteSaisie.h"
#include "Texte_A_Recopier.h"

using namespace std;
using namespace sf;

void TexteSaisie::setCharfont(int n, Font& font)
{
	LoadFont(font);
	cont_[n].setFont(font);
}

void TexteSaisie::setCont(int n, string txt) 
{
	cont_[n].setString(txt);
}

void TexteSaisie::setCharCol(int n, Color color) 
{
	cont_[n].setFillColor(color);

}


void TexteSaisie::setCharPosit(int n, float a, float b) 
{
	cont_[n].setPosition(a, b);

}

void TexteSaisie::afficherTexte(RenderWindow& window)
{
	int taille = cont_.size();

	for (int i=0;i<taille;i++)
	{
		window.draw(cont_[i]);
	}
}

void TexteSaisie::suppchar()
{
	cont_.pop_back();
}

void TexteSaisie::reset()
{
	int n = cont_.size();
	for (int k = 0; k < n; k++) {
		cont_.pop_back();
	}
}

void TexteSaisie::addchar(Text& text)
{
	cont_.push_back(text);
}

Text TexteSaisie::getText()
{
	Text string;
	for (int k = 0; k < cont_.size(); k++) 
	{
		string.setString(string.getString() + cont_[k].getString());
	}
	return string;
}
