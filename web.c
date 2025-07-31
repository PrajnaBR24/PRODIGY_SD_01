#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to download webpage using curl
void downloadWebPage(const char *url, const char *filename) {
    char command[512];
    snprintf(command, sizeof(command), "curl -s \"%s\" -o %s", url, filename);
    system(command);
}

// Function to simulate extracting product info
void extractProductInfo(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("Error opening file(s).\n");
        return;
    }

    fprintf(out, "Scraped Lines\n");
    char line[1024];

    // Search for keywords commonly seen in product listings
    while (fgets(line, sizeof(line), in)) {
        if (strstr(line, "product") || strstr(line, "title") ||
            strstr(line, "price") || strstr(line, "₹") || strstr(line, "$") ||
            strstr(line, "name") || strstr(line, "rating")) {
            // Clean newlines for CSV
            line[strcspn(line, "\n")] = 0;
            fprintf(out, "\"%s\"\n", line);
        }
    }

    fclose(in);
    fclose(out);
    printf("Scraping completed. Extracted content saved to '%s'.\n", outputFile);
}

int main() {
    const char *url = "https://example.com"; // Change this to a target site
    const char *inputFile = "webpage.html";
    const char *outputFile = "scraped_data.csv";

    printf("Starting web scraping...\n");

    downloadWebPage(url, inputFile);
    extractProductInfo(inputFile, outputFile);

    return 0;
}