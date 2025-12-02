package hotc;

import java.util.Scanner;
import java.util.ArrayList;
import java.text.DecimalFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

class Product {
    String id;
    String name;
    int stock;
    double price;
    String category;
    
    public Product(String id, String name, int stock, double price) {
        this.id = id;
        this.name = name;
        this.stock = stock;
        this.price = price;
        this.category = id.startsWith("C") ? "CARD" : "PACK";
    }
}

class CartItem {
    Product product;
    int quantity;
    
    public CartItem(Product product, int quantity) {
        this.product = product;
        this.quantity = quantity;
    }
    
    public double getSubtotal() {
        return product.price * quantity;
    }
}

public class HotC {
    static ArrayList<Product> inventory = new ArrayList<>();
    static ArrayList<CartItem> cart = new ArrayList<>();
    static DecimalFormat df = new DecimalFormat("#,##0.00");
    static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        initializeInventory();
        
        System.out.println("╔════════════════════════════════════════════════════════════════╗");
        System.out.println("║          WELCOME TO HEART OF THE CARDS STORE           ║");
        System.out.println("╚════════════════════════════════════════════════════════════════╝");
        System.out.println();
        
        // Get customer information
        System.out.print("CUSTOMER NAME: ");
        String customerName = scanner.nextLine();
        System.out.print("CUSTOMER ADDRESS: ");
        String customerAddress = scanner.nextLine();
        System.out.print("CUSTOMER CONTACT NUMBER: ");
        String customerContact = scanner.nextLine();
        System.out.println();
        
        boolean shopping = true;
        while (shopping) {
            System.out.println("\n═══════════════════════════════════════════════════════════════");
            System.out.println("                         MAIN MENU");
            System.out.println("═══════════════════════════════════════════════════════════════");
            System.out.println("[1] View All Products");
            System.out.println("[2] View Cards Only");
            System.out.println("[3] View Packs Only");
            System.out.println("[4] Add Item to Cart");
            System.out.println("[5] View Cart");
            System.out.println("[6] Proceed to Checkout");
            System.out.println("[7] Exit");
            System.out.println("═══════════════════════════════════════════════════════════════");
            System.out.print("Enter your choice: ");
            
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline
            
            switch (choice) {
                case 1:
                    displayAllProducts();
                    break;
                case 2:
                    displayProductsByCategory("CARD");
                    break;
                case 3:
                    displayProductsByCategory("PACK");
                    break;
                case 4:
                    addToCart();
                    break;
                case 5:
                    viewCart();
                    break;
                case 6:
                    if (cart.isEmpty()) {
                        System.out.println("\n⚠ Your cart is empty! Please add items first.");
                    } else {
                        checkout(customerName, customerAddress, customerContact);
                        shopping = false;
                    }
                    break;
                case 7:
                    System.out.println("\nThank you for visiting Heart of the Cards Store!");
                    shopping = false;
                    break;
                default:
                    System.out.println("\n⚠ Invalid choice! Please try again.");
            }
        }
        
        scanner.close();
    }
    
    static void initializeInventory() {
        // Cards
        inventory.add(new Product("C-001", "Dark Magician", 7, 550.00));
        inventory.add(new Product("C-002", "Blue-Eyes White Dragon", 4, 1172.50));
        inventory.add(new Product("C-003", "Red-Eyes Black Dragon", 12, 320.00));
        inventory.add(new Product("C-004", "Elemental Hero Neos", 18, 220.00));
        inventory.add(new Product("C-005", "Cyber Dragon", 6, 500.50));
        inventory.add(new Product("C-006", "Armed Dragon Lv10", 25, 55.50));
        inventory.add(new Product("C-007", "Stardust Dragon", 11, 233.00));
        inventory.add(new Product("C-008", "Red Dragon Archfiend", 9, 207.00));
        inventory.add(new Product("C-009", "Number 39: Utopia", 13, 223.50));
        inventory.add(new Product("C-010", "Galaxy-Eyes Photon Dragon", 23, 17.50));
        inventory.add(new Product("C-011", "Odd-Eyes Pendulum Dragon", 19, 14.50));
        inventory.add(new Product("C-012", "D/D/D Doom King Armageddon", 30, 3.00));
        inventory.add(new Product("C-013", "Firewall Dragon", 12, 20.50));
        inventory.add(new Product("C-014", "Decode Talker", 17, 17.50));
        inventory.add(new Product("C-015", "Borreload Dragon", 16, 7.50));
        inventory.add(new Product("C-016", "The Winged Dragon of Ra", 5, 450.00));
        inventory.add(new Product("C-017", "Slifer The Sky Dragon", 3, 600.00));
        inventory.add(new Product("C-018", "Obelisk The Tormentor", 2, 800.00));
        inventory.add(new Product("C-019", "Dark Magician Girl", 4, 1502.50));
        inventory.add(new Product("C-020", "Black Luster Soldier - Envoy of the Beginning", 11, 200.50));
        
        // Packs
        inventory.add(new Product("P-001", "Elemental Energy", 96, 250.50));
        inventory.add(new Product("P-002", "Champion Pack: Game One", 24, 487.00));
        inventory.add(new Product("P-003", "Retro Pack 1", 128, 120.50));
        inventory.add(new Product("P-004", "Retro Pack 2", 128, 120.50));
        inventory.add(new Product("P-005", "Lightning Overdrive", 72, 60.00));
    }
    
    static void displayAllProducts() {
        System.out.println("\n╔═════════════════════════════════════════════════════════════════════════════════╗");
        System.out.println("║                          HEART OF THE CARDS STORE                             ║");
        System.out.println("╠═══════════╦═══════════════════════════════════════════════╦═══════════╦═══════════╣");
        System.out.println("║ Product ID║ Product Name                                  ║ In-Stock  ║   Price   ║");
        System.out.println("╠═══════════╬═══════════════════════════════════════════════╬═══════════╬═══════════╣");
        
        for (Product p : inventory) {
            String stockInfo = p.category.equals("CARD") ? p.stock + " Cards" : p.stock + " Packs";
            System.out.printf("║ %-9s ║ %-45s ║ %-9s ║ $%-8s ║%n", 
                p.id, p.name, stockInfo, df.format(p.price));
        }
        
        System.out.println("╚═══════════╩═══════════════════════════════════════════════╩═══════════╩═══════════╝");
    }
    
    static void displayProductsByCategory(String category) {
        System.out.println("\n╔═════════════════════════════════════════════════════════════════════════════════╗");
        System.out.println("║                          " + category + "S AVAILABLE                                     ║");
        System.out.println("╠═══════════╦═══════════════════════════════════════════════╦═══════════╦═══════════╣");
        System.out.println("║ Product ID║ Product Name                                  ║ In-Stock  ║   Price   ║");
        System.out.println("╠═══════════╬═══════════════════════════════════════════════╬═══════════╬═══════════╣");
        
        for (Product p : inventory) {
            if (p.category.equals(category)) {
                String stockInfo = p.category.equals("CARD") ? p.stock + " Cards" : p.stock + " Packs";
                System.out.printf("║ %-9s ║ %-45s ║ %-9s ║ $%-8s ║%n", 
                    p.id, p.name, stockInfo, df.format(p.price));
            }
        }
        
        System.out.println("╚═══════════╩═══════════════════════════════════════════════╩═══════════╩═══════════╝");
    }
    
    static void addToCart() {
        System.out.print("\nEnter Product ID (e.g., C-001 or P-001): ");
        String productId = scanner.nextLine().toUpperCase();
        
        Product product = findProduct(productId);
        if (product == null) {
            System.out.println("⚠ Product not found!");
            return;
        }
        
        System.out.println("\nProduct: " + product.name);
        System.out.println("Available Stock: " + product.stock + " " + (product.category.equals("CARD") ? "Cards" : "Packs"));
        System.out.println("Price: $" + df.format(product.price));
        
        System.out.print("\nEnter quantity: ");
        int quantity = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        if (quantity <= 0) {
            System.out.println("⚠ Invalid quantity!");
            return;
        }
        
        if (quantity > product.stock) {
            System.out.println("⚠ Insufficient stock! Only " + product.stock + " available.");
            return;
        }
        
        // Check if product already in cart
        boolean found = false;
        for (CartItem item : cart) {
            if (item.product.id.equals(productId)) {
                int newQuantity = item.quantity + quantity;
                if (newQuantity > product.stock) {
                    System.out.println("⚠ Cannot add! Total would exceed available stock.");
                    return;
                }
                item.quantity = newQuantity;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cart.add(new CartItem(product, quantity));
        }
        
        System.out.println("✓ Added to cart successfully!");
    }
    
    static void viewCart() {
        if (cart.isEmpty()) {
            System.out.println("\n⚠ Your cart is empty!");
            return;
        }
        
        System.out.println("\n╔═════════════════════════════════════════════════════════════════════════════════╗");
        System.out.println("║                              YOUR SHOPPING CART                                   ║");
        System.out.println("╠═══════════╦═══════════════════════════════════════════╦══════════╦════════════════╣");
        System.out.println("║ Product ID║ Product Name                              ║ Quantity ║   Subtotal     ║");
        System.out.println("╠═══════════╬═══════════════════════════════════════════╬══════════╬════════════════╣");
        
        double total = 0;
        for (CartItem item : cart) {
            System.out.printf("║ %-9s ║ %-41s ║ %-8d ║ $%-13s ║%n", 
                item.product.id, item.product.name, item.quantity, df.format(item.getSubtotal()));
            total += item.getSubtotal();
        }
        
        System.out.println("╠═══════════╩═══════════════════════════════════════════╩══════════╩════════════════╣");
        System.out.printf("║                                                   TOTAL: $%-13s ║%n", df.format(total));
        System.out.println("╚═══════════════════════════════════════════════════════════════════════════════════╝");
    }
    
    static void checkout(String customerName, String customerAddress, String customerContact) {
        System.out.println("\n╔═══════════════════════════════════════════════════════════════╗");
        System.out.println("║                      CHECKOUT                                 ║");
        System.out.println("╚═══════════════════════════════════════════════════════════════╝");
        
        double subtotal = 0;
        for (CartItem item : cart) {
            subtotal += item.getSubtotal();
        }
        
        // Calculate discount based on total quantity
        int totalQuantity = 0;
        for (CartItem item : cart) {
            totalQuantity += item.quantity;
        }
        
        double discountPercent = 0;
        if (totalQuantity >= 1 && totalQuantity <= 2) {
            discountPercent = 0;
        } else if (totalQuantity >= 3 && totalQuantity <= 4) {
            discountPercent = 2;
        } else if (totalQuantity == 5) {
            discountPercent = 4;
        } else if (totalQuantity >= 6 && totalQuantity <= 10) {
            discountPercent = 6;
        } else if (totalQuantity > 10) {
            discountPercent = 10;
        }
        
        double discountAmount = (subtotal * discountPercent) / 100;
        double totalPrice = subtotal - discountAmount;
        
        System.out.println("\nSubtotal: $" + df.format(subtotal));
        System.out.println("Discount (" + discountPercent + "%): -$" + df.format(discountAmount));
        System.out.println("═══════════════════════════════════════");
        System.out.println("TOTAL PRICE: $" + df.format(totalPrice));
        System.out.println();
        
        // Payment
        System.out.println("═══════════════════════════════════════");
        System.out.println("         PAYMENT METHOD");
        System.out.println("═══════════════════════════════════════");
        System.out.println("[1] Cash");
        System.out.println("[2] Credit Card");
        System.out.print("Enter payment method: ");
        int paymentMethod = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        String paymentType = "CASH";
        String cardNumber = "";
        
        if (paymentMethod == 2) {
            paymentType = "CREDIT CARD";
            System.out.print("Credit Card Number: ");
            cardNumber = scanner.nextLine();
            System.out.print("Credit Card PIN: ");
            String pin = scanner.nextLine();
            System.out.println("✓ Card verified!");
        }
        
        System.out.print("\nPaid Amount: $");
        double paidAmount = scanner.nextDouble();
        scanner.nextLine(); // consume newline
        
        double change = paidAmount - totalPrice;
        
        if (change < 0) {
            System.out.println("⚠ Insufficient payment!");
            return;
        }
        
        // Update inventory
        for (CartItem item : cart) {
            item.product.stock -= item.quantity;
        }
        
        // Print Receipt
        printReceipt(customerName, customerAddress, customerContact, subtotal, 
                    discountPercent, discountAmount, totalPrice, paymentType, 
                    cardNumber, paidAmount, change);
        
        System.out.println("\n✓ Transaction completed successfully!");
        System.out.println("Thank you for shopping at Heart of the Cards Store!");
    }
    
    static void printReceipt(String name, String address, String contact, 
                           double subtotal, double discountPercent, double discountAmount,
                           double totalPrice, String paymentType, String cardNumber,
                           double paidAmount, double change) {
        
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        
        System.out.println("\n\n");
        System.out.println("╔═══════════════════════════════════════════════════════════════════════════════════╗");
        System.out.println("║                          HEART OF THE CARDS STORE                                 ║");
        System.out.println("║                              OFFICIAL RECEIPT                                     ║");
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.println("║ Date: " + now.format(formatter) + "                                                     ║");
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.println("║ CUSTOMER INFORMATION                                                              ║");
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.printf("║ Name:    %-72s ║%n", name);
        System.out.printf("║ Address: %-72s ║%n", address);
        System.out.printf("║ Contact: %-72s ║%n", contact);
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.println("║ ITEMS PURCHASED                                                                   ║");
        System.out.println("╠═══════════╦═══════════════════════════════════════════╦══════════╦════════════════╣");
        System.out.println("║ Product ID║ Product Name                              ║ Quantity ║   Subtotal     ║");
        System.out.println("╠═══════════╬═══════════════════════════════════════════╬══════════╬════════════════╣");
        
        for (CartItem item : cart) {
            System.out.printf("║ %-9s ║ %-41s ║ %-8d ║ $%-13s ║%n", 
                item.product.id, item.product.name, item.quantity, df.format(item.getSubtotal()));
        }
        
        System.out.println("╠═══════════╩═══════════════════════════════════════════╩══════════╩════════════════╣");
        System.out.printf("║ Subtotal:                                                          $%-13s ║%n", df.format(subtotal));
        System.out.printf("║ Discount (%.0f%%):                                                   -$%-13s ║%n", discountPercent, df.format(discountAmount));
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.printf("║ TOTAL PRICE:                                                       $%-13s ║%n", df.format(totalPrice));
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.printf("║ Payment Method: %-65s ║%n", paymentType);
        if (paymentType.equals("CREDIT CARD")) {
            System.out.printf("║ Card Number: %-68s ║%n", cardNumber);
        }
        System.out.printf("║ Amount Paid:                                                       $%-13s ║%n", df.format(paidAmount));
        System.out.printf("║ Change:                                                            $%-13s ║%n", df.format(change));
        System.out.println("╠═══════════════════════════════════════════════════════════════════════════════════╣");
        System.out.println("║                    THANK YOU FOR YOUR PURCHASE!                                   ║");
        System.out.println("║                  Heart of the Cards Store - Since 2025                            ║");
        System.out.println("╚═══════════════════════════════════════════════════════════════════════════════════╝");
    }
    
    static Product findProduct(String id) {
        for (Product p : inventory) {
            if (p.id.equalsIgnoreCase(id)) {
                return p;
            }
        }
        return null;
    }
}
