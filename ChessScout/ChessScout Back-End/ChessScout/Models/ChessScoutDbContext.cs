using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace ChessScout.Models;

public partial class ChessScoutDbContext : DbContext
{
    public ChessScoutDbContext()
    {
    }

    public ChessScoutDbContext(DbContextOptions<ChessScoutDbContext> options)
        : base(options)
    {
    }

    public virtual DbSet<FriendRequest> FriendRequests { get; set; }

    public virtual DbSet<Message> Messages { get; set; }

    public virtual DbSet<ScoutProfile> ScoutProfiles { get; set; }

    public virtual DbSet<User> Users { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder) => optionsBuilder.UseSqlServer("Server=DESKTOP-DKKS7HR; Database=ChessScoutDB;Trusted_Connection=True; Encrypt=False");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<FriendRequest>(entity =>
        {
            entity
                .HasNoKey()
                .ToTable("FriendRequest");

            entity.Property(e => e.Uid1).HasColumnName("uid1");
            entity.Property(e => e.Uid2).HasColumnName("uid2");
        });

        modelBuilder.Entity<Message>(entity =>
        {
            entity
                .HasNoKey()
                .ToTable("Message");

            entity.Property(e => e.MessageText)
                .HasMaxLength(5000)
                .IsUnicode(false);
            entity.Property(e => e.Seen).HasColumnName("seen");
            entity.Property(e => e.UidReceiver).HasColumnName("uidReceiver");
            entity.Property(e => e.UidSender).HasColumnName("uidSender");
        });

        modelBuilder.Entity<ScoutProfile>(entity =>
        {
            entity
                .HasNoKey()
                .ToTable("ScoutProfile");

            entity.Property(e => e.Number).HasColumnName("number");
            entity.Property(e => e.Pid).HasColumnName("pid");
            entity.Property(e => e.PlayersName)
                .HasMaxLength(255)
                .IsUnicode(false)
                .HasColumnName("playersName");
            entity.Property(e => e.SaveDate)
                .HasColumnType("date")
                .HasColumnName("saveDate");
            entity.Property(e => e.Uid).HasColumnName("uid");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.HasNoKey();

            entity.Property(e => e.Birthday)
                .HasColumnType("date")
                .HasColumnName("birthday");
            entity.Property(e => e.Country)
                .HasMaxLength(255)
                .IsUnicode(false)
                .HasColumnName("country");
            entity.Property(e => e.Email)
                .HasMaxLength(255)
                .IsUnicode(false)
                .HasColumnName("email");
            entity.Property(e => e.Pass)
                .HasMaxLength(255)
                .IsUnicode(false)
                .HasColumnName("pass");
            entity.Property(e => e.Uid).HasColumnName("uid");
            entity.Property(e => e.Username)
                .HasMaxLength(255)
                .IsUnicode(false)
                .HasColumnName("username");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
