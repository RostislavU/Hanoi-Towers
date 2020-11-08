CREATE TABLE IF NOT EXISTS UsersData (
    id VARCHAR(64) NOT NULL,
    visibleName VARCHAR default NULL,
    points INTEGER default 0,
    userdata BLOB default NULL,
    updateTime INTEGER default 0,
    userAvatar INTEGER default 0,

    FOREIGN KEY(id) REFERENCES NetworkMembers(id)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS Avatars (
    id INTEGER PRIMARY KEY NOT NULL
    user_id VARCHAR(64) NOT NULL,
    data BLOB default NULL,

    FOREIGN KEY(user_id) REFERENCES NetworkMembers(id)
            ON UPDATE CASCADE
            ON DELETE CASCADE
);
