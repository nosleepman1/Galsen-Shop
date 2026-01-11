# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Nom de l'exécutable
TARGET = mangui_shop

# Fichiers sources et objets
SOURCES = main.cpp Utils.cpp Category.cpp Product.cpp User.cpp Sale.cpp Menu.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Utils.hpp Category.hpp Product.hpp User.hpp Sale.hpp Menu.hpp

# Règle principale
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compilation des fichiers objets
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f USERS CATEGORIES PRODUCTS
	rm -rf BILLS
	rm -f ETAT_*.txt

# Nettoyage complet (y compris les données)
cleanall: clean
	@echo "Tous les fichiers ont été supprimés"

# Reconstruction complète
rebuild: clean all

# Exécution
run: $(TARGET)
	./$(TARGET)

# Aide
help:
	@echo "Commandes disponibles:"
	@echo "  make        - Compile le projet"
	@echo "  make clean  - Supprime les fichiers compilés et les données"
	@echo "  make rebuild- Recompile tout le projet"
	@echo "  make run    - Compile et exécute le programme"
	@echo "  make help   - Affiche cette aide"

.PHONY: all clean cleanall rebuild run help