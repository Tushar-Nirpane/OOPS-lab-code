#include <iostream>
#include <string>
using namespace std;

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int readInt(const string& prompt) {
    cout << prompt;
    int x;
    cin >> x;
    cin.ignore(10000, '\n');
    return x;
}

float readFloat(const string& prompt) {
    cout << prompt;
    float x;
    cin >> x;
    cin.ignore(10000, '\n');
    return x;
}

char readChar(const string& prompt) {
    cout << prompt;
    char c;
    cin >> c;
    cin.ignore(10000, '\n');
    return c;
}

class Song {
private:
    int songId;
    string title;
    string artist;
    string album;
    string genre;
    float duration;
    string playlist;
    int playCount;
    bool available;

public:
    Song() {
        songId = 0;
        title = "";
        artist = "";
        album = "";
        genre = "";
        duration = 0.0;
        playlist = "None";
        playCount = 0;
        available = true;
    }

    Song(int id, string t, string ar, string al, string g,
         float d, string pl, bool av) {
        songId = id;
        title = t;
        artist = ar;
        album = al;
        genre = g;
        duration = d;
        playlist = pl;
        playCount = 0;
        available = av;
    }

    Song(const Song& s) {
        songId = s.songId;
        title = s.title;
        artist = s.artist;
        album = s.album;
        genre = s.genre;
        duration = s.duration;
        playlist = s.playlist;
        playCount = s.playCount;
        available = s.available;
    }

    ~Song() {
    }

    int getId() const { return songId; }
    string getTitle() const { return title; }
    string getPlaylist() const { return playlist; }
    int getPlayCount() const { return playCount; }
    bool isAvailable() const { return available; }

    void setPlaylist(const string& pl) { playlist = pl; }
    void incrementPlayCount() { playCount++; }

    void display() const {
        cout << "\nSong ID      : " << songId
             << "\nTitle        : " << title
             << "\nArtist       : " << artist
             << "\nAlbum        : " << album
             << "\nGenre        : " << genre
             << "\nDuration     : " << duration << " min"
             << "\nPlaylist     : " << playlist
             << "\nPlay Count   : " << playCount
             << "\nAvailability : " << (available ? "Available" : "Restricted")
             << endl;
    }
};

class MusicDatabase {
private:
    Song** songs;
    int total;
    int capacity;

    int findIndex(int id) const {
        for (int i = 0; i < total; i++)
            if (songs[i]->getId() == id)
                return i;
        return -1;
    }

    void grow() {
        int newCap = capacity * 2;
        Song** temp = new Song*[newCap];
        for (int i = 0; i < total; i++)
            temp[i] = songs[i];
        delete[] songs;
        songs = temp;
        capacity = newCap;
    }

public:
    MusicDatabase() {
        capacity = 5;
        total = 0;
        songs = new Song*[capacity];
    }

    MusicDatabase(int cap) {
        capacity = (cap > 0) ? cap : 5;
        total = 0;
        songs = new Song*[capacity];
    }

    MusicDatabase(const MusicDatabase& other) {
        capacity = other.capacity;
        total = other.total;
        songs = new Song*[capacity];
        for (int i = 0; i < total; i++)
            songs[i] = new Song(*other.songs[i]);
    }

    ~MusicDatabase() {
        for (int i = 0; i < total; i++)
            delete songs[i];
        delete[] songs;
        cout << "\n[Database memory released]" << endl;
    }

    void addSong() {
        int id = readInt("Enter Song ID: ");
        if (findIndex(id) != -1) {
            cout << "A song with this ID already exists!" << endl;
            return;
        }
        string title = readLine("Enter Song Title: ");
        string artist = readLine("Enter Artist Name: ");
        string album = readLine("Enter Album Name: ");
        string genre = readLine("Enter Genre (Pop/Rock/Classical/Jazz etc.): ");
        float duration = readFloat("Enter Duration (in minutes): ");
        string pl = readLine("Enter Playlist / Category: ");
        char av = readChar("Is the song available for playing? (y/n): ");

        if (total == capacity)
            grow();

        bool available = (av == 'y' || av == 'Y');
        songs[total] = new Song(id, title, artist, album, genre,
                                duration, pl, available);
        total++;
        cout << "Song added successfully!" << endl;
    }

    void displaySong(int id) const {
        int idx = findIndex(id);
        if (idx == -1) {
            cout << "Song not found." << endl;
            return;
        }
        songs[idx]->display();
    }

    void displayAll() const {
        if (total == 0) {
            cout << "The database is empty." << endl;
            return;
        }
        for (int i = 0; i < total; i++)
            songs[i]->display();
    }

    void playSong(int id) {
        int idx = findIndex(id);
        if (idx == -1) {
            cout << "Song not found." << endl;
            return;
        }
        Song* s = songs[idx];
        if (!s->isAvailable()) {
            cout << "Sorry, '" << s->getTitle()
                 << "' is restricted and cannot be played." << endl;
            return;
        }
        s->incrementPlayCount();
        cout << "Now playing: " << s->getTitle()
             << " (Play count: " << s->getPlayCount() << ")" << endl;
    }

    void addToPlaylist(int id, const string& pl) {
        int idx = findIndex(id);
        if (idx == -1) {
            cout << "Song not found." << endl;
            return;
        }
        songs[idx]->setPlaylist(pl);
        cout << "'" << songs[idx]->getTitle()
             << "' added to playlist: " << pl << endl;
    }

    void removeFromPlaylist(int id) {
        int idx = findIndex(id);
        if (idx == -1) {
            cout << "Song not found." << endl;
            return;
        }
        if (songs[idx]->getPlaylist() == "None") {
            cout << "This song is not in any playlist." << endl;
            return;
        }
        cout << "'" << songs[idx]->getTitle() << "' removed from playlist: "
             << songs[idx]->getPlaylist() << endl;
        songs[idx]->setPlaylist("None");
    }

    void viewStatistics() const {
        if (total == 0) {
            cout << "The database is empty." << endl;
            return;
        }

        int availableCount = 0, restrictedCount = 0;
        int bestIdx = 0;

        cout << "\n--- Availability & Play Statistics ---" << endl;
        cout << "Total Songs : " << total << endl;

        for (int i = 0; i < total; i++) {
            Song* s = songs[i];
            cout << "ID " << s->getId()
                 << " | " << s->getTitle()
                 << " | Playlist: " << s->getPlaylist()
                 << " | Plays: " << s->getPlayCount()
                 << " | " << (s->isAvailable() ? "Available" : "Restricted")
                 << endl;

            if (s->isAvailable()) availableCount++;
            else restrictedCount++;

            if (s->getPlayCount() > songs[bestIdx]->getPlayCount())
                bestIdx = i;
        }

        cout << "Available songs : " << availableCount
             << " | Restricted songs : " << restrictedCount << endl;
        cout << "Most played : " << songs[bestIdx]->getTitle()
             << " (" << songs[bestIdx]->getPlayCount() << " plays)" << endl;
    }
};

int main() {
    MusicDatabase db(10);
    int choice;

    do {
        cout << "\n===== Online Music Management System =====" << endl;
        cout << "1. Add a new song" << endl;
        cout << "2. Display song details" << endl;
        cout << "3. Display all songs" << endl;
        cout << "4. Play a song" << endl;
        cout << "5. Add song to playlist" << endl;
        cout << "6. Remove song from playlist" << endl;
        cout << "7. View availability & play statistics" << endl;
        cout << "8. Create a backup copy of the database (copy constructor)" << endl;
        cout << "0. Exit" << endl;

        choice = readInt("Enter your choice: ");

        switch (choice) {
        case 1:
            db.addSong();
            break;
        case 2: {
            int id = readInt("Enter Song ID: ");
            db.displaySong(id);
            break;
        }
        case 3:
            db.displayAll();
            break;
        case 4: {
            int id = readInt("Enter Song ID to play: ");
            db.playSong(id);
            break;
        }
        case 5: {
            int id = readInt("Enter Song ID: ");
            string pl = readLine("Enter Playlist name: ");
            db.addToPlaylist(id, pl);
            break;
        }
        case 6: {
            int id = readInt("Enter Song ID: ");
            db.removeFromPlaylist(id);
            break;
        }
        case 7:
            db.viewStatistics();
            break;
        case 8: {
            MusicDatabase backup(db);
            cout << "Backup created. Showing backup contents:" << endl;
            backup.displayAll();
            break;
        }
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
