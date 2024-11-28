# Boite-musicale-ARDUINO-RaspBerry-

Leggere "TutoSoundScape.doc"

Dans une équipe de 5 personne on a élaboré le soundscape, un objet connecté qui utiliser le starter kit Lora d'Orange.

Projet "Soundscape" : une station méteo connectée qui envoie les données à distance sur un dispositif qui traduit les informations métérologiques en sons. Je me suis occupé de la partie électronique et informatique (Arduino, Lora, Python, Raspberry Pi3)

L'idée est d'avoir un objet qui traduit les données de l'environnement dans des sons qu'on peut écouter dans des moments de détente.

On a construit 2 objets :
- Le premier c'est une station météo imprimée en 3D qui contient des capteurs d'humidité, température, lumière, pollution et vitesse du vent. Grâce au starter kit Lora qui se connecte automatiquement au réseau Lora l'objet envoie ces données sur un site internet. 

- Le deuxième c'est un boitier imprimé avec une imprimante 3D qui contient un raspberry PI3 connecté à un WiFi. Ce dernier exécute en continu un script python qui récupère sur internet les données du premier boitier et, en fonction des données reHackhaton sur l'object connecté Lora.
