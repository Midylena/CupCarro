package com.mechachieve.cupcarro;

import java.util.Collection;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/historicoCupCarro")
public class HistoricoRestCupCarro {
	
	@Autowired
	private HistoricoDaoCupCarro historicoDao;
	
	@GetMapping
	public List<HistoricoCupCarro> get(){
		return historicoDao.findAll();
	}
	
	@GetMapping("/get")
	public Collection<HistoricoCupCarro> hist(){
		return historicoDao.hist();
	}
	
	@PostMapping("/post")
	public String post(@RequestBody HistoricoCupCarro historico) {
		historicoDao.save(historico);
		return "ENVIADO";
	}
}
