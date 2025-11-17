import os
import time

def hauteur(noeud):
    """
    Fonction autonome (helper) qui renvoie la hauteur d'un noeud.
    Renvoie -1 si le noeud est None, sinon lit la hauteur stockée.
    """
    if noeud is None:
        return -1
    return noeud.hauteur


class Node:
    def __init__(self, valeur, parent=None):
        self.valeur = valeur
        self.parent = parent
        self.gauche = None
        self.droit = None
        self.hauteur = 0 # Un nouveau noeud (feuille) a une hauteur de 0

    def actualiser_hauteur(self):
        """Met à jour la hauteur du noeud en se basant sur ses enfants."""
        self.hauteur = 1 + max(hauteur(self.gauche), hauteur(self.droit))

    def rotation_gauche(self):
        """Effectue une rotation gauche sur ce noeud."""
        pivot = self.droit
        enfant_gauche_pivot = pivot.gauche

        # Effectuer la rotation
        pivot.gauche = self
        self.droit = enfant_gauche_pivot

        # Mettre à jour les parents
        pivot.parent = self.parent
        self.parent = pivot
        if enfant_gauche_pivot:
            enfant_gauche_pivot.parent = self

        # Mettre à jour les hauteurs (l'ordre est crucial)
        self.actualiser_hauteur()   # 'self' est maintenant plus bas
        pivot.actualiser_hauteur()  # 'pivot' est maintenant plus haut

        return pivot # Retourne la nouvelle racine du sous-arbre

    def rotation_droite(self):
        """Effectue une rotation droite sur ce noeud."""
        pivot = self.gauche
        enfant_droit_pivot = pivot.droit

        # Effectuer la rotation
        pivot.droit = self
        self.gauche = enfant_droit_pivot

        # Mettre à jour les parents
        pivot.parent = self.parent
        self.parent = pivot
        if enfant_droit_pivot:
            enfant_droit_pivot.parent = self

        # Mettre à jour les hauteurs (l'ordre est crucial)
        self.actualiser_hauteur()   # 'self' est maintenant plus bas
        pivot.actualiser_hauteur()  # 'pivot' est maintenant plus haut

        return pivot # Retourne la nouvelle racine du sous-arbre


    def insererAVL(self, valeur):
        """
        Insère récursivement une valeur dans le sous-arbre 
        et retourne la nouvelle racine de ce sous-arbre.
        (Basé sur votre Snippet 2)
        """
        if valeur < self.valeur:
            if self.gauche is None:
                self.gauche = Node(valeur, parent=self)
            else:
                # La nouvelle racine du sous-arbre gauche est retournée
                self.gauche = self.gauche.insererAVL(valeur)
        
        elif valeur > self.valeur:
            if self.droit is None:
                self.droit = Node(valeur, parent=self)
            else:
                # La nouvelle racine du sous-arbre droit est retournée
                self.droit = self.droit.insererAVL(valeur)
        else:
            # La valeur existe déjà, on ne fait rien
            return self

        # 1. Mettre à jour la hauteur du noeud courant
        self.actualiser_hauteur()
        
        # 2. Équilibrer le noeud courant et retourner la (potentielle) nouvelle racine
        return self.equilibrer()

    def equilibrer(self):
        """
        Vérifie l'équilibre du noeud et effectue les rotations si nécessaire.
        Retourne la nouvelle racine du sous-arbre.
        (Basé sur votre Snippet 3)
        """
        # Calcule le facteur d'équilibre
        balance = hauteur(self.gauche) - hauteur(self.droit)

        # Cas 1: Déséquilibre Gauche (balance == 2)
        if balance == 2:
            # Cas Gauche-Gauche (Rotation Droite simple)
            # Votre code : hauteur(self.gauche.gauche) > hauteur(self.gauche.droit)
            # C'est correct, mais utiliser le facteur d'équilibre est plus robuste:
            if hauteur(self.gauche.gauche) >= hauteur(self.gauche.droit):
                return self.rotation_droite()
            # Cas Gauche-Droite (Rotation Gauche puis Droite)
            else:
                self.gauche = self.gauche.rotation_gauche()
                return self.rotation_droite()
        
        # Cas 2: Déséquilibre Droit (balance == -2)
        elif balance == -2:
            # Cas Droit-Droit (Rotation Gauche simple)
            if hauteur(self.droit.droit) >= hauteur(self.droit.gauche):
                return self.rotation_gauche()
            # Cas Droit-Gauche (Rotation Droite puis Gauche)
            else:
                self.droit = self.droit.rotation_droite()
                return self.rotation_gauche()

        # Pas de déséquilibre, on retourne le noeud tel quel
        return self

# -------------------------------------------------------------------
# 3. CLASSE AVL (La classe "principale" qui gère l'arbre)
# -------------------------------------------------------------------

class AVL:
    def reader(self):
        base_dir = os.path.dirname(os.path.abspath(__file__))
        file_path = os.path.join(base_dir, "../library_input.txt")

        try:
            with open(file_path, "r") as f:
                data = f.read().split()
                data = [int(x) for x in data]

            idx = 0
            n = data[idx]; idx += 1
            stock_id = data[idx:idx+n]
            idx += n

            m = data[idx]; idx += 1
            stock_search = data[idx:idx+m]

        except FileNotFoundError:
            print(f"Erreur d'ouverture du fichier : {file_path}")
        except Exception as e:
            print(f"Erreur inattendue : {e}")

        return stock_id, stock_search

    def __init__(self):
        self.racine = None

    def estVide(self):
        return self.racine is None

    def insererAVL(self, valeur):
        """
        Insère une valeur dans l'arbre.
        (Basé sur votre Snippet 1)
        """
        if self.estVide():
            self.racine = Node(valeur)
        else:
            # La méthode insererAVL du Node peut retourner une nouvelle racine
            # (si la racine de l'arbre a été changée par une rotation)
            # Il est crucial de la réassigner.
            self.racine = self.racine.insererAVL(valeur)
            self.racine.parent = None # S'assurer que la racine n'a pas de parent

    # --- Fonctions d'aide pour l'affichage ---
    def __str__(self):
        if self.racine is None:
            return "<Arbre Vide>"
        return self._afficher_arbre(self.racine, 0)

    def _afficher_arbre(self, noeud, niveau):
        if noeud is None:
            return ""
        
        s = ""
        # Afficher le sous-arbre droit d'abord (pour une rotation visuelle de 90°)
        s += self._afficher_arbre(noeud.droit, niveau + 1)
        
        # Afficher le noeud courant
        s += "    " * niveau + "-> " + str(noeud.valeur) + f" (h={noeud.hauteur})\n"
        
        # Afficher le sous-arbre gauche
        s += self._afficher_arbre(noeud.gauche, niveau + 1)
        
        return s
    def rechercher(self, valeur):
        """
        Recherche une valeur dans l'arbre de manière itérative.
        Retourne True si la valeur est trouvée, False sinon.
        """
        noeud_actuel = self.racine
        
        while noeud_actuel is not None:
            # Cas 1: On a trouvé la valeur
            if valeur == noeud_actuel.valeur:
                return True
            
            # Cas 2: La valeur cherchée est plus petite
            elif valeur < noeud_actuel.valeur:
                noeud_actuel = noeud_actuel.gauche
            
            # Cas 3: La valeur cherchée est plus grande
            else:
                noeud_actuel = noeud_actuel.droit
        
        # Cas 4: On a atteint le bas de l'arbre (None) sans trouver la valeur
        return False

# --- Création de l'arbre ---
mon_arbre = AVL()
id_list, search_list = mon_arbre.reader()
for valeur in id_list:
    mon_arbre.insererAVL(valeur)

# print("Arbre final construit :")
# print(mon_arbre)

'''
# 1. Chercher une valeur qui existe
valeur_a_trouver = 418230322
if mon_arbre.rechercher(valeur_a_trouver):
    print(f"Résultat : La valeur {valeur_a_trouver} a été trouvée !")
else:
    print(f"Résultat : La valeur {valeur_a_trouver} n'est pas dans l'arbre.")
'''

start_time = time.perf_counter()

for i in (search_list):
    if mon_arbre.rechercher(i):
        print("YES")
    else:
        print("NO") 

end_time = time.perf_counter()    # point de fin

elapsed_time = end_time - start_time
print(f"\nExecution time: {elapsed_time:.6f} seconds")

