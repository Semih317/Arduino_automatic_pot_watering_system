# Otomatik Sulama Sistemi 🌿💧

Saksı bitkileri yetiştirmek için tasarlanmış, enerji tasarruflu ve tamamen otomatik bir sulama sistemi. Bu proje, toprak nem seviyesini anlık olarak izlemek için bir analog nem sensörü kullanır; toprak kuruduğunda ise **Arduino Nano** aracılığıyla röle modülünü tetikleyerek 5V su pompasını otomatik olarak çalıştırır. Sistem durumu ve veriler 16x2 LCD ekranda anlık olarak gösterilir.

## 🚀 Öne Çıkan Özellikler

- Aşırı veya yetersiz sulamayı önlemek için toprağın nem durumu sürekli analiz edilir.
- Kontrol devresi (Arduino ve sensörler) ile yüksek akım çeken yük (su pompası) tamamen bağımsız güç kaynaklarından beslenir. Bu sayede motor parazitleri engellenir ve Arduino'nun kilitlenmesi/reset atması önlenir.
- LCD ekranın arka ışık katotu (-) doğrudan Arduino'nun dijital `D8` pinine bağlanmıştır. Işık buton ile isteğe bağlı açılır, sistem boşta beklerken kapatılarak pil ömrü maksimuma çıkarılır.
- Paylaşılan standart devre şeması; herhangi bir 5V USB adaptör, bilgisayar bağlantısı veya standart pillerle tamamen uyumludur. Eğer powerbank kullanılacaksa ve bir süre sonra powerbank kendi kendini kapatıyorsa, düşük akım modu açılmalıdır. Eğer bu mod yoksa, Arduino`nun 5V ve GND pinlerini birleştiren 220 ohm değerinde direnç kullanılabilir. Bu direnç powerbank`den çekilen akımı artırarak kapanmamasını sağlamaktadır. 
  Bazı powerbankler için 1 adet direnç yeterli olmamaktadır. Bu durumda dirençlerin sayısı artırılabilir. (Ben bu senaryoyu yaşadım ve 4 adet 220 ohm direnç kullanarak bu sorunu çözdüm.)

## 🛠️ Kullanılan Donanımlar

- Arduino Nano
- Toprak Nem Sensörü (YL-69 (FC-28))
- DHT11
- 5V Röle Modülü
- 6V Dalgıç Su Pompası
- 16x2 LCD Ekran
- Powerbank (Arduino için) & Harici Pil Bloğu (Pompa için)
- Kaydırmalı Anahtar, 10k ohm potansiyometre, 10 k ohm direnç, 220 ohm direç, 1000 uF kondansatör
- Breadboard, dişi-erkek ve erkek-erkek jumper kablo, bakır tel (pil bloğunu birleştirmek için)

## 📊 Devre Şeması

Devre şeması circuit.svg olarak yüklenmiştir.
