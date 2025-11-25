#include "include/Caserma.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include "include/gestioneEccezioni.hpp"
#include <set>
#include <algorithm>
#include <map>

void menu();
Grado scegliGrado();

int main() {
    Caserma caserma;
    int scelta = 0;
    IDGenerator gen;
   
    do {
        menu();
        std::cout << "\nScelta: ";
        std::cin >> scelta;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input non valido.\n";
            continue;
        }

        switch (scelta) {
            case 1: {
                std::string nome;
                std::cout << "Inserisci nome del militare: ";
                std::cin.ignore();
                std::getline(std::cin, nome);
                Grado grado = scegliGrado();
                int nuovoID=-1;
                try {
                    nuovoID =gen.generaID();
                    std::cout<< "\n\nGenerato ID: "  <<nuovoID << "\n";
                }  catch (const std::exception& e) {
                    std::cout << "\n\nErrore nella generazione ID: " << e.what() << "\n";  //metodo della classe std::exeption che restituisce una stringa
                    break;
                }
                caserma.aggiungiPersonale(std::make_unique<Personale>(nuovoID, nome, grado));
                std::cout << "\n\nPersonale aggiunto con ID " << nuovoID << "\n";
                break;
            }

            case 2: {
            
                        std::cout << "Inserisci tipo di mezzo: \n";
                        std::cout << "1. Jeep" << std::endl;
                        std::cout << "2. Camion" << std::endl;
                        std::cout << "3. Elicottero" << std::endl;
                        std::cout << "4. Carro Armato" << std::endl;
                        std::cout << "5. Humvee" << std::endl;
                        
                        int tipoScelta=0;
                        std::cout << "\nScelta: ";
                        std::cin >> tipoScelta;
                        if (std::cin.fail() || tipoScelta < 2 || tipoScelta > 6) {
                            std::cout << "\n\nInput non valido.\n";
                            continue;
                        }
                       
                        std::string tipo;
                        switch(tipoScelta)
                        {
                            case 1: tipo="Jeep"; break;
                            case 2: tipo="Camion"; break;
                            case 3: tipo="Elicottero"; break;
                            case 4: tipo="Carro Armato"; break;
                            case 5: tipo="Humvee"; break;
                        }
                         
                int nuovoID=-1;
                try {
                    nuovoID = gen.generaID();
                    std::cout<< "Generato ID: "  <<nuovoID << "\n";
                }  catch (const std::exception& e) {
                    std::cout << "Errore nella generazione ID: " << e.what() << "\n";  
                    break;
                }
                try {
                    caserma.aggiungiMezzo(std::make_unique<Mezzo>(nuovoID, tipo));
                    std::cout << "Mezzo aggiunto con ID " << nuovoID << "\n";
                } catch (const std::exception& e) {
                    std::cout << "Errore: " << e.what() << "\n";
                }
                break;
            
        }

            case 3: {
                std::string descrizione;
                std::cout << "Descrizione missione: ";
                std::cin.ignore();
                std::getline(std::cin, descrizione);

                caserma.mostraPersonale();
                std::cout << "Inserisci ID del personale da assegnare (termina con -1): ";
                std::vector<int> idPersonale;
                int idp;
                while (std::cin >> idp && idp != -1)
                    idPersonale.push_back(idp);

                caserma.mostraMezzi();
                std::cout << "Inserisci ID dei mezzi da assegnare (termina con -1): ";
                std::vector<int> idMezzi;
                int idm;
                while (std::cin >> idm && idm != -1)
                    idMezzi.push_back(idm);

                // Ora chiediamo per ogni mezzo quali personale della missione devono essere assegnati a quel mezzo
                std::map<int, std::vector<int>> assegnamentiMezzi;
                std::set<int> personaleAssegnatoGlobale;
                for (int mezzoId : idMezzi) {
                    std::cout << "Inserisci gli ID del personale da assegnare al mezzo " << mezzoId << " (termina con -1): ";
                    int pid;
                    std::vector<int> idPersonalePerMezzo;
                    while (std::cin >> pid && pid != -1) {
                        // Verifica che il pid sia stato selezionato tra quelli della missione
                        if (std::find(idPersonale.begin(), idPersonale.end(), pid) == idPersonale.end()) {
                            std::cout << "Errore: il personale con ID " << pid << " non è stato selezionato per la missione. Creazione fallita.\n";
                            idPersonalePerMezzo.clear();
                            personaleAssegnatoGlobale.clear();
                            assegnamentiMezzi.clear();
                            goto abort_missione;
                        }
                        // Verifica che non sia già assegnato ad altro mezzo
                        if (personaleAssegnatoGlobale.count(pid) > 0) {
                            std::cout << "Errore: il personale con ID " << pid << " è già assegnato ad un altro mezzo in questa missione. Creazione fallita.\n";
                            idPersonalePerMezzo.clear();
                            personaleAssegnatoGlobale.clear();
                            assegnamentiMezzi.clear();
                            goto abort_missione;
                        }
                        idPersonalePerMezzo.push_back(pid);
                        personaleAssegnatoGlobale.insert(pid);
                    }
                    assegnamentiMezzi[mezzoId] = idPersonalePerMezzo;
                }

                // Controllo: verifica che ogni mezzo abbia almeno 2 e non più di 6 persone (e poi verificheremo la capienza del mezzo nel Caserma)
                for (auto& kv : assegnamentiMezzi) {
                    if (kv.second.size() < 2 || kv.second.size() > 6) {
                        std::cout << "Errore: ogni mezzo deve avere almeno 2 e al massimo 6 persone assegnate. Creazione fallita.\n";
                        goto abort_missione;
                    }
                }

                caserma.creaMissione(descrizione, idPersonale, idMezzi, assegnamentiMezzi);
                break;

                abort_missione:
                    ; // ritorna al menu principale
                break;
            }

            case 4:
                caserma.mostraPersonale();
                break;

            case 5:
                caserma.mostraMezzi();
                break;

            case 6:
                caserma.mostraMissioni();
                break;

            case 0:
                std::cout << "Uscita...\n";
                break;

            default:
                std::cout << "Scelta non valida!\n";
        }

    } while (scelta != 0);

    return 0;
}

void menu() {
    std::cout << "\n========== GESTIONE CASERMA ==========" << std::endl;
    std::cout << "1. Aggiungi personale" << std::endl;
    std::cout << "2. Aggiungi mezzo" << std::endl;
    std::cout << "3. Crea missione" << std::endl;
    std::cout << "4. Mostra personale" << std::endl;
    std::cout << "5. Mostra mezzi" << std::endl;
    std::cout << "6. Mostra missioni" << std::endl;
    std::cout << "0. Esci" << std::endl;
}

Grado scegliGrado() {
    int g;
    std::cout << "Scegli grado:\n";
    std::cout << "1. Soldato\n2. Caporale\n3. Sergente\n4. Tenente\n5. Capitano\n6. Maggiore\n";
    std::cout << "Scelta: ";
    std::cin >> g;

    switch (g) {
        case 1: return Grado::SOLDATO;
        case 2: return Grado::CAPORALE;
        case 3: return Grado::SERGENTE;
        case 4: return Grado::TENENTE;
        case 5: return Grado::CAPITANO;
        case 6: return Grado::MAGGIORE;
        default: return Grado::SOLDATO;
    }
}
