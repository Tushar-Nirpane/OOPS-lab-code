#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Song {
    string title, artist, album, genre, playlist;
    int songID, duration, playCount;
    bool restricted;
public:
    static int alive;
    Song() : songID(0), duration(0), playCount(0), restricted(false) { alive++; }
    Song(const Song &o) : title(o.title), artist(o.artist), album(o.album), genre(o.genre),
        playlist(o.playlist), songID(o.songID), duration(o.duration),
        playCount(o.playCount), restricted(o.restricted) { alive++; }
    ~Song() { alive--; }

    void addRecord() {
        cout << "Title: "; getline(cin >> ws, title);
        cout << "Song ID: "; cin >> songID; cin.ignore();
        cout << "Artist: "; getline(cin, artist);
        cout << "Album: "; getline(cin, album);
        cout << "Genre (Pop/Rock/Classical/Jazz): "; getline(cin, genre);
        cout << "Duration (seconds): "; cin >> duration; cin.ignore();
        cout << "Restricted? (1=yes, 0=no): "; cin >> restricted; cin.ignore();
        playlist = "";
    }
    void display() const {
        cout << "ID: " << songID << " | " << title << " | Artist: " << artist
             << " | Album: " << album << " | Genre: " << genre
             << " | Duration: " << duration << "s | Playlist: "
             << (playlist.empty() ? "none" : playlist) << "\n";
    }
    void play() {
        if (restricted) { cout << title << " is restricted, cannot play.\n"; return; }
        playCount++;
        cout << "Playing " << title << " (play count " << playCount << ")\n";
    }
    void addToPlaylist(const string &p) { playlist = p; cout << "Added to playlist " << p << "\n"; }
    void removeFromPlaylist() { cout << "Removed from playlist " << playlist << "\n"; playlist = ""; }
    void stats() const {
        cout << title << " | Available: " << (restricted ? "No" : "Yes")
             << " | Play count: " << playCount << "\n";
    }
    int getID() const { return songID; }
};
int Song::alive = 0;

int main() {
    {
        // Scoped so every Song is destroyed before the final live-object count is printed.
        vector<Song> songs;
        int choice, id;
        do {
            cout << "\n1.Add song 2.Display 3.Play 4.Add to playlist 5.Remove from playlist "
                 << "6.Availability/stats 0.Exit\nChoice: ";
            if (!(cin >> choice)) break;
            if (choice == 1) {
                Song s; s.addRecord(); songs.push_back(s);
            } else if (choice >= 2 && choice <= 6) {
                cout << "Song ID: "; cin >> id;
                bool found = false;
                for (Song &s : songs) {
                    if (s.getID() != id) continue;
                    found = true;
                    if (choice == 2) s.display();
                    else if (choice == 3) s.play();
                    else if (choice == 4) {
                        string p;
                        cout << "Playlist name: ";
                        getline(cin >> ws, p);
                        s.addToPlaylist(p);
                    }
                    else if (choice == 5) s.removeFromPlaylist();
                    else s.stats();
                }
                if (!found) cout << "Song not found.\n";
            }
        } while (choice != 0);
    }
    cout << "Song objects alive: " << Song::alive << "\n";
    return 0;
}
