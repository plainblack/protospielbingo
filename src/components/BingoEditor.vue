<template>
  <div class="container">
    <h1>Protospiel Bingo Generator</h1>
    <p>
      This app will let you generate custom Protospiel Bingo Cards for your
      convention.
    </p>

    <h2>General</h2>

    <div class="row">
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating mb-3">
          <input
            v-model="gameName"
            type="text"
            class="form-control"
            id="gameName"
            placeholder="Protospiel Bingo"
          />
          <label for="gameName">Game Name</label>
        </div>
      </div>
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating mb-3">
          <input
            v-model="numberOfCards"
            type="number"
            class="form-control"
            id="numberOfCards"
            placeholder="Protospiel Bingo"
          />
          <label for="numberOfCards">Number of Cards</label>
        </div>
      </div>
    </div>

    <h2>Colors</h2>
    <div class="row">
      <div class="col col-sm-3 mb-3">
        <label for="wildColor" class="d-block">Wild</label>
        <color-input
          v-model="colorIndex.wild"
          id="wildColor"
          format="hex string"
        />
      </div>
      <div class="col col-sm-3 mb-3">
        <label for="mechanicsColor" class="d-block">Mechanics</label>
        <color-input
          v-model="colorIndex.mechanics"
          id="mechanicsColor"
          format="hex string"
        />
      </div>
      <div class="col col-sm-3 mb-3">
        <label for="genresColor" class="d-block">Genres</label>
        <color-input
          v-model="colorIndex.genres"
          id="genresColor"
          format="hex string"
        />
      </div>
      <div class="col col-sm-3 mb-3">
        <label for="themesColor" class="d-block">Themes</label>
        <color-input
          v-model="colorIndex.themes"
          id="themesColor"
          format="hex string"
        />
      </div>
      <div class="col col-sm-3 mb-3">
        <label for="componentsColor" class="d-block">Components</label>
        <color-input
          v-model="colorIndex.components"
          id="componentsColor"
          format="hex string"
        />
      </div>
      <div class="col col-sm-3 mb-3">
        <label for="designersColor" class="d-block">Designers</label>
        <color-input
          v-model="colorIndex.designers"
          id="designersColor"
          format="hex string"
        />
      </div>
      <div class="col col-sm-3 mb-3">
        <label for="playersColor" class="d-block">Players</label>
        <color-input
          v-model="colorIndex.players"
          id="playersColor"
          format="hex string"
        />
      </div>
    </div>

    <h2>Categories</h2>
    <p>
      Create a comma separated list of values you wish to be randomized into
      your bingo cards.
    </p>

    <div class="row">
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating">
          <textarea
            v-model="mechanicsCSV"
            class="form-control"
            placeholder="Worker Placement, Trick Taking, etc"
            id="mechanicsCSV"
            style="height: 100px"
          ></textarea>
          <label for="mechanicsCSV">Mechanics (minimum 4)</label>
        </div>
      </div>
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating">
          <textarea
            v-model="genresCSV"
            class="form-control"
            placeholder="Co-op, Party, etc"
            id="genresCSV"
            style="height: 100px"
          ></textarea>
          <label for="genresCSV">Genres (minimum 4)</label>
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating">
          <textarea
            v-model="themesCSV"
            class="form-control"
            placeholder="Zombies, Aliens, etc"
            id="themesCSV"
            style="height: 100px"
          ></textarea>
          <label for="themesCSV">Themes (minimum 3)</label>
        </div>
      </div>
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating">
          <textarea
            v-model="componentsCSV"
            class="form-control"
            placeholder="Tiles, Cards, Dice, etc"
            id="componentsCSV"
            style="height: 100px"
          ></textarea>
          <label for="componentsCSV">Components (minimum 4)</label>
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating">
          <textarea
            v-model="designersCSV"
            class="form-control"
            placeholder="New, Experienced, Foreign, etc"
            id="designersCSV"
            style="height: 100px"
          ></textarea>
          <label for="designersCSV">Designers (minimum 2)</label>
        </div>
      </div>
      <div class="col-12 col-md-6 mb-3">
        <div class="form-floating">
          <textarea
            v-model="playersCSV"
            class="form-control"
            placeholder="1, 2, 3, 4"
            id="playersCSV"
            style="height: 100px"
          ></textarea>
          <label for="playersCSV">Players (minimum 3)</label>
        </div>
      </div>
    </div>

    <div class="row">
      <div class="col">
        <button type="button" class="btn btn-success" @click="drawCards()">
          Generate Bingo Cards PDF
        </button>
      </div>
      <div class="col">&copy; 2019-2022 Clever Playing Cards</div>
    </div>
  </div>
</template>

<script>
import Papa from "papaparse";
import { jsPDF } from "jspdf";
import ColorInput from "vue-color-input";
export default {
  name: "BingoEditor",
  components: { ColorInput },
  props: {},
  data() {
    return {
      mechanicsCSV:
        "Worker Placement, Card / Dice Drafting, Area Control, Trick-Trump, Simultaneous Action, Pick Up & Deliver, Roll & Write, Action Selection, Social Deduction, Set Collection, Unique Mechanic, Press your Luck, Auction / Bidding",
      genresCSV:
        "Cooperative, Party, Dexterity, Take That, Light / Filler, Heavy / Complex, Trivia, Euro",
      themesCSV:
        "War Game, Abstract, Animals, Space, Aliens, Zombies, Historical, Nautical, Educational, Trains, Fantasy, Economics, Unique Theme, Location- based",
      componentsCSV:
        "Dice, Cards, Cubes, (Actual) Meeples, Acrylic Pieces, Homemade Pieces, Tiles, Wooden Pieces, Player Mat, Reference Card, Score Track, Color Blind Friendly, Unique Component, Standees / Pawns, Game Board",
      designersCSV:
        "New-to-you Designer, In-State Designer, Out-of-State Designer",
      playersCSV: "Solo, 2 Players, 3 Players, 4 Players, 5+ Players",
      numberOfCards: 2,
      colorIndex: {
        wild: "#50af32",
        themes: "#9e62b1",
        mechanics: "#0021f5",
        genres: "#7d4b0f",
        components: "#eb3323",
        players: "#e4af54",
        designers: "#000000",
      },
      gameName: "Protospiel Bingo " + new Date().getFullYear(),
    };
  },
  computed: {
    mechanics() {
      return Papa.parse(this.mechanicsCSV).data[0];
    },
    genres() {
      return Papa.parse(this.genresCSV).data[0];
    },
    themes() {
      return Papa.parse(this.themesCSV).data[0];
    },
    components() {
      return Papa.parse(this.componentsCSV).data[0];
    },
    designers() {
      return Papa.parse(this.designersCSV).data[0];
    },
    players() {
      return Papa.parse(this.playersCSV).data[0];
    },
  },
  methods: {
    initCardCells() {
      return [
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0],
      ];
    },
    rand(max = 32767) {
      return Math.floor(Math.random() * max);
    },
    addWild(cells) {
      let self = this;
      let a = (self.rand() % 3) + 1; // 1, 2 or 3 (first column is 0)
      let e = ((a + (self.rand() % 2) + 1 - 1) % 3) + 1; // 1, 2, or 3, but not what a was, above
      let c = self.rand() % 5;
      while (c == 2 || c == a || c == e) {
        c = self.rand() % 5;
      }
      let b = self.rand() % 5;
      while (b == a || b == c || b == e) {
        b = self.rand() % 5;
      }
      let d = self.rand() % 5;
      while (d == a || d == b || d == c || d == e) {
        d = self.rand() % 5;
      }
      cells[0][a] = { category: "wild", text: "Any Game" };
      cells[1][b] = { category: "wild", text: "Any Game" };
      cells[2][c] = { category: "wild", text: "Any Game" };
      cells[3][d] = { category: "wild", text: "Any Game" };
      cells[4][e] = { category: "wild", text: "Any Game" };
    },
    addCategory(cells, category, count) {
      let self = this;
      let strings = self.shuffleArray(self[category]);
      for (let i = 0; i < count; i++) {
        let string = strings.pop();
        let j = self.rand() % 25; // this is the cell to put it in
        while (cells[parseInt(j / 5)][j % 5] != 0) {
          // keep looking for an open cell
          j = self.rand() % 25;
        }
        cells[parseInt(j / 5)][j % 5] = { category: category, text: string };
      }
    },
    shuffleArray(unshuffled) {
      return unshuffled
        .map((value) => ({ value, sort: Math.random() }))
        .sort((a, b) => a.sort - b.sort)
        .map(({ value }) => value);
    },
    generateCard() {
      let self = this;
      let cells = self.initCardCells();
      self.addWild(cells);
      self.addCategory(cells, "themes", 3);
      self.addCategory(cells, "mechanics", 4);
      self.addCategory(cells, "genres", 4);
      self.addCategory(cells, "components", 4);
      self.addCategory(cells, "players", 3);
      self.addCategory(cells, "designers", 2);
      return cells;
    },
    drawCells(doc, x, y) {
      let self = this;
      let cells = self.generateCard();
      let width = 5;
      let height = width;
      let cellWidth = width / 5;
      let cellHeight = height / 5;

      // draw grid
      doc.rect(x, y, width, height);
      for (let i = 1; i < 5; i++) {
        doc.line(x, y + cellHeight * i, x + width, y + cellHeight * i);
        doc.line(x + cellWidth * i, y, x + cellWidth * i, y + height);
      }

      // write cell content
      for (let i = 0; i < 5; i++) {
        for (let j = 0; j < 5; j++) {
          doc.setFont("helvetica", "normal", "bold");
          doc.setFontSize(10);
          doc.setTextColor(self.colorIndex[cells[i][j].category]);
          doc.text(
            cells[i][j].text,
            x + cellWidth * (i + 0.49),
            y + cellHeight * (j + 0.15),
            {
              align: "center",
              maxWidth: cellWidth,
            }
          );
          doc.setFont("helvetica", "normal", "normal");
          doc.setFontSize(9);
          doc.text(
            "GN:\n\nDI:",
            x + cellWidth * (i + 0.05),
            y + cellHeight * (j + 0.6),
            {
              align: "left",
              maxWidth: cellWidth,
            }
          );
        }
      }
    },
    drawHeader(doc, x, y) {
      let self = this;
      doc.setFont("helvetica", "normal", "bold");
      doc.setFontSize(26);
      doc.setTextColor("#000000");
      doc.text(self.gameName, x + 2.5, y + 0.35, {
        align: "center",
        maxWidth: 5,
      });
      doc.setFontSize(12);
      doc.text(
        "Your name: ___________________    Badge Number: _____",
        x + 2.5,
        y + 0.7,
        {
          align: "center",
          maxWidth: 5,
        }
      );
      doc.setFont("helvetica", "normal", "normal");
      doc.setFontSize(10);
      doc.text(
        "Play games, fill in squares, get 5 in a row to WIN!",
        x + 2.5,
        y + 1,
        {
          align: "center",
          maxWidth: 5,
        }
      );
    },
    drawFooter(doc, x, y) {
      let self = this;
      doc.setFont("helvetica", "normal", "normal");
      doc.setFontSize(10);

      doc.text(
        "For each game you play test for a designer (not you) that matches a square on",
        x,
        y
      );
      doc.text("this bingo card in ", x, y + 0.2);
      doc.setFont("helvetica", "normal", "bold");
      doc.setTextColor(self.colorIndex.themes);
      doc.text("Theme,", x + 1.1, y + 0.2);
      doc.setTextColor(self.colorIndex.mechanics);
      doc.text("Mechanic,", x + 1.65, y + 0.2);
      doc.setTextColor(self.colorIndex.genres);
      doc.text("Genre,", x + 2.38, y + 0.2);
      doc.setTextColor(self.colorIndex.designers);
      doc.text("Designer,", x + 2.87, y + 0.2);
      doc.setTextColor(self.colorIndex.components);
      doc.text("Component,", x + 3.55, y + 0.2);
      doc.setFont("helvetica", "normal", "normal");
      doc.setTextColor("#000000");
      doc.text("or", x + 4.4, y + 0.2);
      doc.setFont("helvetica", "normal", "bold");
      doc.setTextColor(self.colorIndex.players);
      doc.text("Players,", x + 4.57, y + 0.2);
      doc.setFont("helvetica", "normal", "normal");
      doc.setTextColor("#000000");
      doc.text(
        "fill in the game name [GN] and have the designer initial [DI] it.",
        x,
        y + 0.4
      );
      doc.setFontSize(9);
      doc.setTextColor("#0000ff");
      doc.setFont("helvetica", "normal", "bold");
      doc.text(
        "** Each game may only be used once even though it may satisfy multiple squares. **",
        x,
        y + 0.7
      );
      doc.text("** Designers can NOT fill in their own game. **", x, y + 0.9);
      doc.text("** Limit 1 prize per player. **", x, y + 1.1);
      doc.setFont("helvetica", "normal", "normal");
      doc.setTextColor("#000000");
      doc.text("Copyright 2019-2022 Clever Playing Cards", x, y + 1.3);
    },
    drawCards() {
      let self = this;
      let doc = new jsPDF({
        orientation: "landscape",
        unit: "in",
        format: "letter",
      });
      doc.setLineWidth("0.0125");
      let maxPages = Math.ceil(self.numberOfCards / 2);
      for (let pageNumber = 0; pageNumber < maxPages; pageNumber++) {
        for (let x of [0.25, 5.75]) {
          self.drawCells(doc, x, 1.5);
          self.drawHeader(doc, x, 0.25);
          self.drawFooter(doc, x, 6.75);
        }
        if (pageNumber + 1 < maxPages) {
          doc.addPage("letter", "landscape");
        }
      }
      doc.save("test.pdf");
    },
  },
};
</script>

<style></style>
