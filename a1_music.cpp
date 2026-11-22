#include <iostream>
#include <string>
using namespace std;

class Song {
private:
    int id, duration, plays;
    string title, artist, album, genre, playlist;
    bool available;

public:

  
    Song() {
        id = duration = plays = 0;
        title = artist = album = genre = "";
        playlist = "None";
        available = true;
    }


    Song(int i, string t, string a, string al, string g, int d) {
        id = i;
        title = t;
        artist = a;
        album = al;
        genre = g;
        duration = d;
        plays = 0;
        playlist = "None";
        available = true;
    }

   
    Song(const Song &s) {
        id = s.id;
        title = s.title;
        artist = s.artist;
        album = s.album;
        genre = s.genre;
        duration = s.duration;
        plays = s.plays;
        playlist = s.playlist;
        available = s.available;
    }

  
    ~Song() {
        
    }

    
    void input() {
        cout << "\nEnter Song ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Song Title: ";
        getline(cin, title);

        cout << "Enter Artist Name: ";
        getline(cin, artist);

        cout << "Enter Album Name: ";
        getline(cin, album);

        cout << "Enter Genre: ";
        getline(cin, genre);

        cout << "Enter Duration (seconds): ";
        cin >> duration;

        available = true;
        plays = 0;
        playlist = "None";
    }

    
    void display() {
        cout << "\nSong ID       : " << id;
        cout << "\nSong Title    : " << title;
        cout << "\nArtist Name   : " << artist;
        cout << "\nAlbum Name    : " << album;
        cout << "\nGenre         : " << genre;
        cout << "\nDuration      : " << duration << " seconds";
        cout << "\nPlaylist      : " << playlist;
        cout << "\nAvailability  : "
             << (available ? "Available" : "Restricted");
        cout << "\nPlay Count    : " << plays << endl;
    }

    
    void play() {
        if (available) {
            plays++;
            cout << "\nPlaying Song: " << title << endl;
            cout << "Total Plays: " << plays << endl;
        }
        else {
            cout << "\nSong is restricted and cannot be played!" << endl;
        }
    }

   
    void addPlaylist() {
        cin.ignore();
        cout << "\nEnter Playlist Name: ";
        getline(cin, playlist);

        cout << "Song added to playlist successfully!" << endl;
    }

    
    void removePlaylist() {
        playlist = "None";
        cout << "\nSong removed from playlist!" << endl;
    }

    
    void changeAvailability() {
        available = !available;

        cout << "\nSong Availability Updated: "
             << (available ? "Available" : "Restricted") << endl;
    }

    
    void showStats() {
        cout << "\n--- Song Statistics ---" << endl;
        cout << "Song Title   : " << title << endl;
        cout << "Availability : "
             << (available ? "Available" : "Restricted") << endl;
        cout << "Total Plays  : " << plays << endl;
        cout << "Playlist     : " << playlist << endl;
    }
};

int main() {

    Song *songs[100];
    int count = 0;
    int choice, index;

    do {
        cout << "\n===== ONLINE MUSIC MANAGEMENT SYSTEM =====";
        cout << "\n1. Add New Song";
        cout << "\n2. Display Song Details";
        cout << "\n3. Play a Song";
        cout << "\n4. Add to Playlist";
        cout << "\n5. Remove from Playlist";
        cout << "\n6. View Song Statistics";
        cout << "\n7. Change Song Availability";
        cout << "\n8. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                if (count < 100) {
                    Song temp;
                    temp.input();

                    
                    songs[count] = new Song(temp);

                    count++;
                    cout << "\nSong Added Successfully!" << endl;
                }
                else {
                    cout << "\nDatabase is Full!" << endl;
                }
                break;

            case 2:
                cout << "\nEnter Song Number (1 to " << count << "): ";
                cin >> index;

                if (index >= 1 && index <= count)
                    songs[index - 1]->display();
                else
                    cout << "\nInvalid Song Number!" << endl;
                break;

            case 3:
                cout << "\nEnter Song Number: ";
                cin >> index;

                if (index >= 1 && index <= count)
                    songs[index - 1]->play();
                else
                    cout << "\nInvalid Song Number!" << endl;
                break;

            case 4:
                cout << "\nEnter Song Number: ";
                cin >> index;

                if (index >= 1 && index <= count)
                    songs[index - 1]->addPlaylist();
                else
                    cout << "\nInvalid Song Number!" << endl;
                break;

            case 5:
                cout << "\nEnter Song Number: ";
                cin >> index;

                if (index >= 1 && index <= count)
                    songs[index - 1]->removePlaylist();
                else
                    cout << "\nInvalid Song Number!" << endl;
                break;

            case 6:
                cout << "\nEnter Song Number: ";
                cin >> index;

                if (index >= 1 && index <= count)
                    songs[index - 1]->showStats();
                else
                    cout << "\nInvalid Song Number!" << endl;
                break;

            case 7:
                cout << "\nEnter Song Number: ";
                cin >> index;

                if (index >= 1 && index <= count)
                    songs[index - 1]->changeAvailability();
                else
                    cout << "\nInvalid Song Number!" << endl;
                break;

            case 8:
                cout << "\nExiting Music Management System..." << endl;
                break;

            default:
                cout << "\nInvalid Choice!" << endl;
        }

    } while (choice != 8);

    
    for (int i = 0; i < count; i++) {
        delete songs[i];
    }

    return 0;
}
