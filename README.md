# Arduino basse consommation -> 0.02mA en Sommeil
 Comment mon Arduino nano tient 3 ans sur une batterie de 1000mAh ?
Je vous montre comment augmenter l’autonomie de votre arduino nano par 2000 en 5 minutes !
Les arduino sont pratiques avec leur port USB et convertisseur série, led Power et régulateurs … mais tout cela consomme énormément et en mode production, cela est inutile.



## Bien commencer

Pour les tests at afin de mesurer le courant consommé, je branche l'arduino directement a une source 5V ou 3.3V sur le Pin +5 de l'arduino
ici le schema
![Schema ](test_5V_simple.jpg?raw=true "schema test")


je vous invite a venir regarder mon tuto sur youtube en français sur ce projet : https://youtu.be/JonCgBIgUcw

### Requis Logiciel
* [Arduino IDE](https://www.arduino.cc) - arduino IDE
* [le code qui fait passer l'arduino en mode sommeil ](Blink_Sleep_mode/Blink_Sleep_mode.ino) - Le code

### Requis Hardware: Sur aliexpress !
Arduino Nano (at328/AT328P) ->  http://bit.ly/2WKxqZE

Convertisseur USB_Série CH340 -> http://s.click.aliexpress.com/e/l2zlBPvQ

Condensateurs polarisé 100nF pack condensateur  -> http://s.click.aliexpress.com/e/CftrcmKk



## Preparation
* Suppression du regulateur
* Suppression de la Led d'alimentation
* Suppression du convertisseur usb/serie

Je vous invite a venir voir les étapes plus en details sur mon tuto -> http://bit.ly/2KJLYBo


## Les Tests : 

Dans cette exemple j’utilise un AT168m@16 Mhz sous 5V et 3.3V et je vais retirer certains composant.
Voici les résultat de mes tests:

 * Sans modification:

Mode Normal/Actif : 13mA

Mode Sommeil : 3mA

 * Avec Modification ( suppression régulateur, led alimentation et convertisseur série):

En 5V : 

Mode Normal(Actif):  13 mA

Mode Sommeil: 0.026mA ( 26µA )

En 3.3V : 

Mode Normal:  5.8mA

Mode Sommeil: 0.022mA ( 22µA )

Conclusion:

avec une batterie de 1200mA (Lien ici http://bit.ly/2Kmgdzf )  l’Arduino obtient une autonomie de 3 ans et demi:
formule de calcul:

1000mAh / 0.022mAh = 54 545 heures 
54 545 h / (24 *365 jours) = 6.22 ans 
et on applique le coefficient d’usure de  0.7 : 
6.22 * 0.7 =  3.63 ans



## Contribution

Toutes contribution est la bienvenue sur ce projet.


## Auteur

* **Djamal Guellati** - *Initial work* - [Defdjamel](https://github.com/Defdjamel)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
