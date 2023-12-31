﻿// <auto-generated />
using System;
using ChessScout.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;

#nullable disable

namespace ChessScout.Migrations
{
    [DbContext(typeof(ChessScoutDbContext))]
    [Migration("20230308175127_initial")]
    partial class initial
    {
        /// <inheritdoc />
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "7.0.3")
                .HasAnnotation("Relational:MaxIdentifierLength", 128);

            SqlServerModelBuilderExtensions.UseIdentityColumns(modelBuilder);

            modelBuilder.Entity("ChessScout.Models.FriendRequest", b =>
                {
                    b.Property<int?>("Uid1")
                        .HasColumnType("int")
                        .HasColumnName("uid1");

                    b.Property<int?>("Uid2")
                        .HasColumnType("int")
                        .HasColumnName("uid2");

                    b.ToTable("FriendRequest", (string)null);
                });

            modelBuilder.Entity("ChessScout.Models.Message", b =>
                {
                    b.Property<string>("MessageText")
                        .HasMaxLength(5000)
                        .IsUnicode(false)
                        .HasColumnType("varchar(5000)");

                    b.Property<int?>("Seen")
                        .HasColumnType("int")
                        .HasColumnName("seen");

                    b.Property<int?>("UidReceiver")
                        .HasColumnType("int")
                        .HasColumnName("uidReceiver");

                    b.Property<int?>("UidSender")
                        .HasColumnType("int")
                        .HasColumnName("uidSender");

                    b.ToTable("Message", (string)null);
                });

            modelBuilder.Entity("ChessScout.Models.ScoutProfile", b =>
                {
                    b.Property<int?>("Number")
                        .HasColumnType("int")
                        .HasColumnName("number");

                    b.Property<int?>("Pid")
                        .HasColumnType("int")
                        .HasColumnName("pid");

                    b.Property<string>("PlayersName")
                        .HasMaxLength(255)
                        .IsUnicode(false)
                        .HasColumnType("varchar(255)")
                        .HasColumnName("playersName");

                    b.Property<DateTime?>("SaveDate")
                        .HasColumnType("date")
                        .HasColumnName("saveDate");

                    b.Property<int?>("Uid")
                        .HasColumnType("int")
                        .HasColumnName("uid");

                    b.ToTable("ScoutProfile", (string)null);
                });

            modelBuilder.Entity("ChessScout.Models.User", b =>
                {
                    b.Property<DateTime?>("Birthday")
                        .HasColumnType("date")
                        .HasColumnName("birthday");

                    b.Property<string>("Country")
                        .HasMaxLength(255)
                        .IsUnicode(false)
                        .HasColumnType("varchar(255)")
                        .HasColumnName("country");

                    b.Property<string>("Email")
                        .HasMaxLength(255)
                        .IsUnicode(false)
                        .HasColumnType("varchar(255)")
                        .HasColumnName("email");

                    b.Property<string>("Pass")
                        .HasMaxLength(255)
                        .IsUnicode(false)
                        .HasColumnType("varchar(255)")
                        .HasColumnName("pass");

                    b.Property<int?>("Uid")
                        .HasColumnType("int")
                        .HasColumnName("uid");

                    b.Property<string>("Username")
                        .HasMaxLength(255)
                        .IsUnicode(false)
                        .HasColumnType("varchar(255)")
                        .HasColumnName("username");

                    b.ToTable("Users");
                });
#pragma warning restore 612, 618
        }
    }
}
