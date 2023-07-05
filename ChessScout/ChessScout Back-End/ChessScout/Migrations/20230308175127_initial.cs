using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ChessScout.Migrations
{
    /// <inheritdoc />
    public partial class initial : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "FriendRequest",
                columns: table => new
                {
                    uid1 = table.Column<int>(type: "int", nullable: true),
                    uid2 = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                });

            migrationBuilder.CreateTable(
                name: "Message",
                columns: table => new
                {
                    uidSender = table.Column<int>(type: "int", nullable: true),
                    uidReceiver = table.Column<int>(type: "int", nullable: true),
                    MessageText = table.Column<string>(type: "varchar(5000)", unicode: false, maxLength: 5000, nullable: true),
                    seen = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                });

            migrationBuilder.CreateTable(
                name: "ScoutProfile",
                columns: table => new
                {
                    pid = table.Column<int>(type: "int", nullable: true),
                    uid = table.Column<int>(type: "int", nullable: true),
                    number = table.Column<int>(type: "int", nullable: true),
                    playersName = table.Column<string>(type: "varchar(255)", unicode: false, maxLength: 255, nullable: true),
                    saveDate = table.Column<DateTime>(type: "date", nullable: true)
                },
                constraints: table =>
                {
                });

            migrationBuilder.CreateTable(
                name: "Users",
                columns: table => new
                {
                    uid = table.Column<int>(type: "int", nullable: true),
                    username = table.Column<string>(type: "varchar(255)", unicode: false, maxLength: 255, nullable: true),
                    pass = table.Column<string>(type: "varchar(255)", unicode: false, maxLength: 255, nullable: true),
                    email = table.Column<string>(type: "varchar(255)", unicode: false, maxLength: 255, nullable: true),
                    country = table.Column<string>(type: "varchar(255)", unicode: false, maxLength: 255, nullable: true),
                    birthday = table.Column<DateTime>(type: "date", nullable: true)
                },
                constraints: table =>
                {
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "FriendRequest");

            migrationBuilder.DropTable(
                name: "Message");

            migrationBuilder.DropTable(
                name: "ScoutProfile");

            migrationBuilder.DropTable(
                name: "Users");
        }
    }
}
